#include "main_application/plot_objects/plot_object_base/plot_object_base.h"

void PlotObjectBase::modifyShader(const GLuint program_id_)
{
    glUniform3f(glGetUniformLocation(program_id_, "vertex_color"), color_.red, color_.green, color_.blue);
}

bool PlotObjectBase::isPersistent() const
{
    return is_persistent_;
}

std::string PlotObjectBase::getName() const
{
    return name_.data;
}

std::pair<Vec3Dd, Vec3Dd> PlotObjectBase::getMinMaxVectors()
{
    if (!min_max_calculated_)
    {
        min_max_calculated_ = true;
        findMinMax();
    }
    return std::pair<Vec3Dd, Vec3Dd>(min_vec, max_vec);
}

size_t PlotObjectBase::getNumDimensions() const
{
    return num_dimensions_;
}

PlotObjectBase::PlotObjectBase() {}

PlotObjectBase::PlotObjectBase(std::unique_ptr<const ReceivedData> received_data, const FunctionHeader& hdr)
    : received_data_(std::move(received_data))
{
    const uint64_t num_data_bytes = received_data_->getNumDataBytes();
    if (num_data_bytes == 0)
    {
        throw std::runtime_error("No data bytes!");
    }
    min_max_calculated_ = false;
    visualize_has_run_ = false;

    type_ = hdr.get(FunctionHeaderObjectType::FUNCTION).as<Function>();
    data_type_ = hdr.get(FunctionHeaderObjectType::DATA_TYPE).as<DataType>();

    num_bytes_per_element_ = dataTypeToNumBytes(data_type_);
    num_elements_ = hdr.get(FunctionHeaderObjectType::NUM_ELEMENTS).as<uint32_t>();
    num_data_bytes_ = received_data_->getNumDataBytes();
    num_dimensions_ = getNumDimensionsFromFunction(type_);

    num_bytes_for_one_vec_ = num_bytes_per_element_ * num_elements_;

    /*if((num_dimensions_ * num_bytes_for_one_vec_) != num_data_bytes_)
    {
        throw std::runtime_error("Expected number of bytes does not match the actual number of bytes!");
    }*/

    const Properties props(hdr.getValues());

    assignProperties(props);

    data_ptr_ = received_data_->getDataPointer();
}

void PlotObjectBase::assignProperties(const Properties& props)
{
    is_persistent_ = props.hasProperty(PropertyType::PERSISTENT);

    line_type_ = props.hasProperty(PropertyType::LINE_STRIP) ? GL_LINES : GL_LINE_STRIP;

    if (props.hasProperty(PropertyType::NAME))
    {
        name_ = props.getProperty<Name>();
    }
    else
    {
        name_ = Name("<undef-name>");
    }

    if (props.hasProperty(PropertyType::COLOR))
    {
        const Color col = props.getProperty<Color>();
        color_.red = static_cast<float>(col.red) / 255.0f;
        color_.green = static_cast<float>(col.green) / 255.0f;
        color_.blue = static_cast<float>(col.blue) / 255.0f;
    }
    else
    {
        color_ = RGBTripletf(0.1, 0.2, 0.1);
    }

    if (props.hasProperty(PropertyType::ALPHA))
    {
        // TODO: Alpha should be a number between 0-100
        const Alpha alp = props.getProperty<Alpha>();
        alpha_ = static_cast<float>(alp.data) / 255.0f;
    }
    else
    {
        alpha_ = 1.0f;
    }

    if (props.hasProperty(PropertyType::EDGE_COLOR))
    {
        const EdgeColor ec = props.getProperty<EdgeColor>();
        edge_color_.red = static_cast<float>(ec.red) / 255.0f;
        edge_color_.green = static_cast<float>(ec.green) / 255.0f;
        edge_color_.blue = static_cast<float>(ec.blue) / 255.0f;
    }
    else
    {
        edge_color_ = RGBTripletf(1.0f, 1.0f, 1.0f);
    }

    if (props.hasProperty(PropertyType::FACE_COLOR))
    {
        const FaceColor fc = props.getProperty<FaceColor>();
        face_color_.red = static_cast<float>(fc.red) / 255.0f;
        face_color_.green = static_cast<float>(fc.green) / 255.0f;
        face_color_.blue = static_cast<float>(fc.blue) / 255.0f;
    }
    else
    {
        face_color_ = RGBTripletf(0.1f, 0.2f, 0.3f);
    }

    if (props.hasProperty(PropertyType::COLOR_MAP))
    {
        color_map_ = props.getProperty<ColorMap>().data;
    }
    else
    {
        color_map_ = ColorMapType::JET;
    }

    if (props.hasProperty(PropertyType::LINE_WIDTH))
    {
        const LineWidth lw = props.getProperty<LineWidth>();
        line_width_ = lw.data;
    }
    else
    {
        line_width_ = 1.0f;
    }

    if (props.hasProperty(PropertyType::POINT_SIZE))
    {
        const PointSize ps = props.getProperty<PointSize>();
        point_size_ = ps.data;
    }
    else
    {
        point_size_ = 1.0f;
    }

    if (props.hasProperty(PropertyType::LINE_STYLE))
    {
        line_style_ = props.getProperty<LineStyle>();
    }
    else
    {
        line_style_ = LineStyle("");
    }
}

PlotObjectBase::~PlotObjectBase() {}