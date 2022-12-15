#ifndef TEST_APPLICATIONS_ADVANCED_TESTS_CPP_TESTS_APPEND_PROPERTIES_H_
#define TEST_APPLICATIONS_ADVANCED_TESTS_CPP_TESTS_APPEND_PROPERTIES_H_

#include <unistd.h>

#include "dvs/dvs.h"

using namespace dvs;

namespace append_properties
{

void testBasic()
{
    const size_t num_elements = 100;

    const Vector<double> x = linspaceFromBoundariesAndCount<double>(0.0, 5.0, num_elements);
    const Vector<double> y = dvs::sin(x);

    setCurrentElement("p_view_0");
    clearView();

    setProperties(properties::SLOT0, properties::Color::Blue(), properties::LineWidth(10));
    setProperties(properties::SLOT0, properties::LineWidth(20));
    plot(x, y, properties::SLOT0, properties::Alpha(127), properties::INTERPOLATE_COLORMAP);

    usleep(1000 * 1000);
    setProperties(properties::SLOT0, properties::Color::Red());
}

}  // namespace append_properties

#endif  // TEST_APPLICATIONS_ADVANCED_TESTS_CPP_TESTS_APPEND_PROPERTIES_H_
