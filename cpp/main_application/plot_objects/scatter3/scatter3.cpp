#include "main_application/plot_objects/scatter3/scatter3.h"

uint8_t* convertData3DOuter(const uint8_t* const input_data,
                            const DataType data_type,
                            const size_t num_elements,
                            const size_t num_bytes_per_element,
                            const size_t num_bytes_for_one_vec);

Scatter3D::Scatter3D(std::unique_ptr<const ReceivedData> received_data, const FunctionHeader& hdr, const ShaderCollection shader_collection)
    : PlotObjectBase(std::move(received_data), hdr, shader_collection)
{
    if (type_ != Function::SCATTER3)
    {
        throw std::runtime_error("Invalid function type for Scatter3D!");
    }

    points_ptr_ =
        convertData3DOuter(data_ptr_, data_type_, num_elements_, num_bytes_per_element_, num_bytes_for_one_vec_);

    glGenVertexArrays(1, &vertex_buffer_array_);
    glBindVertexArray(vertex_buffer_array_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_elements_ * 3, points_ptr_, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /*float* color_data = new float[num_elements_ * 3];

    for(size_t k = 0; k < (num_elements_ * 3); k += 3)
    {
        color_data[k] = color_.red;
        color_data[k + 1] = color_.green;
        color_data[k + 2] = color_.blue;
    }

    glGenBuffers(1, &color_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_elements_ * 3, color_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );*/

}

void Scatter3D::modifyShader()
{
    PlotObjectBase::modifyShader();
    glUniform1f(glGetUniformLocation(shader_collection_.basic_plot_shader.programId(), "point_size"), point_size_);
}

void Scatter3D::findMinMax()
{
    std::tie<Vec3Dd, Vec3Dd>(min_vec, max_vec) =
        findMinMaxFromThreeVectors(data_ptr_, num_elements_, num_bytes_for_one_vec_, data_type_);
}

void Scatter3D::render()
{
    glBindVertexArray(vertex_buffer_array_);
    glDrawArrays(GL_POINTS, 0, num_elements_);
    glBindVertexArray(0);
}

Scatter3D::~Scatter3D()
{
    delete[] points_ptr_;
}
