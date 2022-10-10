#ifndef TEST_APPLICATIONS_BASIC_TESTS_CPP_TESTS_H_
#define TEST_APPLICATIONS_BASIC_TESTS_CPP_TESTS_H_

#include <algorithm>

#include "dvs/dvs.h"

using namespace dvs;

void testSurf()
{
    const int num_rows = 20, num_cols = 25;
    Matrix<double> x(num_rows, num_cols), y(num_rows, num_cols), z(num_rows, num_cols);

    const double inc = 0.4;
    for (int r = 0; r < num_rows; r++)
    {
        for (int c = 0; c < num_cols; c++)
        {
            const double rd = static_cast<double>(r - 5) * inc;
            const double cd = static_cast<double>(c - 5) * inc * 2;
            x(r, c) = c;
            y(r, c) = r;
            z(r, c) = 50.0 * std::sin(std::sqrt(rd * rd + cd * cd));
        }
    }

    setCurrentElement("view_00");
    clearView();
    surf(x, y, z, properties::EdgeColor(0, 0, 0), properties::FaceColor(255, 0, 0));

    setCurrentElement("view_01");
    clearView();
    surf(x, y, z, properties::EdgeColor::None(), properties::ColorMap::Jet());

    setCurrentElement("view_02");
    clearView();
    surf(x, y, z, properties::EdgeColor::None(), properties::ColorMap::Jet(), properties::INTERPOLATE_COLORMAP);
}

void testScatter()
{
    Vector<double> x(20), y(20);
    Vector<float> xf(20), yf(20);

    double t = 0.0;

    for (size_t k = 0; k < 20; k++)
    {
        xf(k) = k;
        yf(k) = 5.0 * std::sin(3.0 * t);

        x(k) = xf(k);
        y(k) = yf(k);

        t = t + 0.1;
    }

    setCurrentElement("view_00");
    clearView();
    axis({0.0, -8.0, -3.3}, {32.0, 32.0, 6.6});

    plot(xf, yf, properties::Color(212, 14, 55));
    scatter(x, y, properties::Color(12, 14, 55));
    scatter(x, y + 1.0, properties::Color::Black(), properties::PointSize(11));
    scatter(x, y + 2.0, properties::Color::Cyan(), properties::PointSize(12), properties::ScatterStyle::Square());
    scatter(x, y + 3.0, properties::Color::Magenta(), properties::PointSize(13), properties::ScatterStyle::Disc());
    scatter(x, y + 4.0, properties::Color::Blue(), properties::PointSize(14), properties::ScatterStyle::Plus());
    scatter(x, y + 5.0, properties::Color::Red(), properties::PointSize(14), properties::ScatterStyle::Cross());
}

void testScatter3()
{
    const size_t num_elements = 14600;
    Vector<double> x(num_elements), y(num_elements), z(num_elements);

    double t0 = 0.0f, t1 = 0.0f, t2 = 0.0f, y0 = 0.0f, z0 = 0.0f;

    for (size_t k = 0; k < num_elements; k++)
    {
        const float xf = 7.0 * cos(t0) + 20.0f;
        const float yf = 7.0 * sin(t0) - 110.0f;
        const float zf = 0.0f;

        const Vec3f v0 = rotationMatrixY<float>(t1) * Vec3f(xf, yf, zf);
        const Vec3f v1 = rotationMatrixZ<float>(t2) * (v0 + Vec3f(50.0f, y0, 0.0f));

        x(k) = v1.x;
        y(k) = v1.y;
        z(k) = v1.z + z0 - 70;
        t0 = t0 + 0.3;
        t1 = t1 - 0.01;
        t2 = t2 + 0.002;
        y0 = y0 + 0.05;
        z0 = z0 + 0.02;
    }

    setCurrentElement("view_00");
    clearView();

    axis({-128.0, -128.0, -128.0}, {128.0, 128.0, 128.0});
    plot3(x, y, z, properties::Color(255, 14, 255), properties::LineWidth(1));
    scatter3(x, y, z, properties::Color(12, 14, 55));
    scatter3(x, y, z + 1.0, properties::Color::Black(), properties::PointSize(11));
    scatter3(x, y, z + 2.0, properties::Color::Cyan(), properties::PointSize(12), properties::ScatterStyle::Square());
    scatter3(x, y, z + 3.0, properties::Color::Magenta(), properties::PointSize(13), properties::ScatterStyle::Disc());
    scatter3(x, y, z + 4.0, properties::Color::Blue(), properties::PointSize(14), properties::ScatterStyle::Plus());
    scatter3(x, y, z + 5.0, properties::Color::Red(), properties::PointSize(14), properties::ScatterStyle::Cross());
}

void testPlotCollection()
{
    const size_t num_elements = 40;
    Vector<double> x0(num_elements), y0(num_elements), x1(num_elements), y1(num_elements), x2(num_elements),
        y2(num_elements);

    double t = 0.0;

    for (size_t k = 0; k < num_elements; k++)
    {
        const double kd = k;
        x0(k) = 10.0 * cos(t);
        y0(k) = kd * 0.05 * 10.0 * sin(t) + 0.2;

        x1(k) = 14.0 * cos(t);
        y1(k) = kd * 0.07 * 11.0 * sin(t) + 0.3;

        x2(k) = 9.0 * cos(t);
        y2(k) = kd * 0.08 * 15.0 * sin(t) + 0.4;
        t = t + 0.1;
    }

    std::vector<std::reference_wrapper<Vector<double>>> pc_x = {x0, x1, x2};
    std::vector<std::reference_wrapper<Vector<double>>> pc_y = {y0, y1, y2};

    setCurrentElement("view_00");
    clearView();

    plotCollection(pc_x, pc_y, properties::Color(0, 0, 0));
    scatter(x0, y0, properties::Color(212, 14, 55), properties::PointSize(10));
    scatter(x1, y1, properties::Color(0, 14, 55), properties::PointSize(10));
    scatter(x2, y2, properties::Color(0, 255, 55), properties::PointSize(10));

    std::vector<Vector<double>> pcm_x;
    std::vector<Vector<double>> pcm_y;

    auto rand_num = [](void) -> double { return static_cast<double>(rand() % 1001) / 1000.0; };

    std::vector<size_t> np = {50, 50, 50, 50, 56};

    for (size_t k = 0; k < 30; k++)
    {
        const size_t num_elems = (rand() % 20) + 50;
        Vector<double> x(num_elems), y(num_elems);

        t = 0.0;

        const double t_inc = rand_num() / 100.0 + 0.05;
        const double x_a = rand_num() * 3.0;
        const double y_a = rand_num() * 3.0;
        const double x_o = rand_num() * 10.0;
        const double y_o = rand_num() * 10.0;

        for (size_t i = 0; i < num_elems; i++)
        {
            x(i) = x_a * cos(t) + x_o;
            y(i) = y_a * t * sin(t) + y_o;
            t += t_inc;
        }
        pcm_x.push_back(std::move(x));
        pcm_y.push_back(std::move(y));
    }

    setCurrentElement("view_01");
    clearView();

    for (size_t k = 0; k < pcm_x.size(); k++)
    {
        scatter(pcm_x[k], pcm_y[k], properties::Color(255, 0, 0), properties::PointSize(10));
    }

    plotCollection(pcm_x, pcm_y, properties::Color(0, 0, 0));
}

void testPlotCollection3()
{
    const size_t num_elements = 40;
    Vector<double> x0(num_elements), y0(num_elements), z0(num_elements), x1(num_elements), y1(num_elements),
        z1(num_elements), x2(num_elements), y2(num_elements), z2(num_elements);

    double t = 0.0;

    for (size_t k = 0; k < num_elements; k++)
    {
        const double kd = k;
        x0(k) = 10.0 * cos(t);
        y0(k) = kd * 0.05 * 10.0 * sin(t) + 0.2;
        z0(k) = kd * 0.05 * 10.0 * cos(t) * sin(t) + 0.3;

        x1(k) = 14.0 * cos(t);
        y1(k) = kd * 0.07 * 11.0 * sin(t) + 0.3;
        z1(k) = kd * 0.07 * 11.0 * sin(t) * cos(t) + 0.3;

        x2(k) = 9.0 * cos(t);
        y2(k) = kd * 0.08 * 15.0 * sin(t) + 0.4;
        z2(k) = kd * 0.08 * 15.0 * sin(t) * cos(t) + 0.4;
        t = t + 0.1;
    }

    std::vector<std::reference_wrapper<Vector<double>>> pc_x = {x0, x1, x2};
    std::vector<std::reference_wrapper<Vector<double>>> pc_y = {y0, y1, y2};
    std::vector<std::reference_wrapper<Vector<double>>> pc_z = {z0, z1, z2};

    setCurrentElement("view_00");
    clearView();

    plotCollection3(pc_x, pc_y, pc_z, properties::Color(0, 0, 0));
    scatter3(x0, y0, z0, properties::Color(212, 14, 55), properties::PointSize(10));
    scatter3(x1, y1, z1, properties::Color(0, 14, 55), properties::PointSize(10));
    scatter3(x2, y2, z2, properties::Color(0, 255, 55), properties::PointSize(10));

    std::vector<Vector<double>> pcm_x;
    std::vector<Vector<double>> pcm_y;
    std::vector<Vector<double>> pcm_z;

    auto rand_num = [](void) -> double { return static_cast<double>(rand() % 1001) / 1000.0; };

    std::vector<size_t> np = {50, 50, 50, 50, 56};

    for (size_t k = 0; k < 30; k++)
    {
        const size_t num_elems = (rand() % 20) + 50;
        Vector<double> x(num_elems), y(num_elems), z(num_elems);

        t = 0.0;

        const double t_inc = rand_num() / 100.0 + 0.05;
        const double x_a = rand_num() * 3.0;
        const double y_a = rand_num() * 3.0;
        const double z_a = rand_num() * 3.0;
        const double x_o = rand_num() * 10.0;
        const double y_o = rand_num() * 10.0;
        const double z_o = rand_num() * 10.0;

        for (size_t i = 0; i < num_elems; i++)
        {
            x(i) = x_a * cos(t) + x_o;
            y(i) = y_a * t * sin(t) + y_o;
            z(i) = z_a * t * sin(t) * cos(t) + z_o;
            t += t_inc;
        }
        pcm_x.push_back(std::move(x));
        pcm_y.push_back(std::move(y));
        pcm_z.push_back(std::move(z));
    }

    setCurrentElement("view_01");
    clearView();

    for (size_t k = 0; k < pcm_x.size(); k++)
    {
        scatter3(pcm_x[k], pcm_y[k], pcm_z[k], properties::Color(255, 0, 0), properties::PointSize(10));
    }

    plotCollection3(pcm_x, pcm_y, pcm_z, properties::Color(0, 0, 0));
}

void testPlot()
{
    const size_t num_elements = 30;
    Vector<float> x(num_elements), y(num_elements), z(num_elements);

    setCurrentElement("view_00");
    clearView();

    const size_t num_points = 6;
    Vector<float> xp(num_points), yp(num_points), zp(num_points);

    xp(0) = 0.0;
    xp(1) = 1.0;
    xp(2) = 2.2;
    xp(3) = 3.0;
    xp(4) = 3.5;
    xp(5) = 3.5;

    yp(0) = 0.0;
    yp(1) = 3.5;
    yp(2) = 3.5;
    yp(3) = 2.5;
    yp(4) = 4.0;
    yp(5) = 2.0;

    zp.fill(0.01f);

    axis({-1.0, -1.0, -1.0}, {5.0, 5.0, 1.0});
    plot(xp, yp, properties::LineWidth(60), properties::LineStyle::Dashed(), properties::Color(200, 200, 200));
    scatter3(xp, yp, zp, properties::PointSize(10), properties::Color(255, 0, 0));

    setCurrentElement("view_01");
    float t = 0.0;

    for (size_t k = 0; k < num_elements; k++)
    {
        x(k) = 10.0 * cos(t) + 20.0;
        y(k) = 10.0 * sin(t) + 20.0 + k;
        z(k) = 0.01f;

        t = t + 0.3;
    }

    axis({0.0, 16.0, -1.0}, {50.0, 64.0, 1.0});
    plot(x + 3.0f, y, properties::Color(0, 255, 255), properties::LineWidth(1));
    plot(x + 4.0f, y, properties::Color(212, 14, 55), properties::LineWidth(1), properties::LineStyle::Dashed());
    plot(x + 5.0f, y, properties::Color(212, 255, 55), properties::LineWidth(4), properties::LineStyle::Dotted());
    plot(x + 6.0f, y, properties::Color(212, 14, 255), properties::LineWidth(7), properties::LineStyle::LongDashed());
    plot(x + 6.0f,
         y,
         properties::Color(212, 14, 255),
         properties::LineWidth(7),
         properties::LineStyle::LongDashed(),
         properties::PERSISTENT);
    scatter3(x + 3.0f, y, z, properties::Color::Black(), properties::PointSize(14));

    setCurrentElement("view_02");
    clearView();
    t = 0.0;
    x.resize(num_elements * 10);
    y.resize(num_elements * 10);
    z.resize(num_elements * 10);

    for (size_t k = 0; k < (num_elements * 10); k++)
    {
        x(k) = 10.0f * cos(t) + 20.0f;
        y(k) = 10.0f * sin(t) + 20.0f + static_cast<float>(k) / 10.0f;
        z(k) = 0.01f;

        t = t + 0.03;
    }

    axis({0.0, 16.0, -1.0}, {50.0, 64.0, 1.0});
    plot(x + 3.0f, y, properties::Color(0, 255, 255), properties::LineWidth(1));
    plot(x + 4.0f, y, properties::Color(212, 14, 55), properties::LineWidth(1), properties::LineStyle::Dashed());
    plot(x + 5.0f, y, properties::Color(212, 255, 55), properties::LineWidth(4), properties::LineStyle::Dotted());
    plot(x + 6.0f, y, properties::Color(212, 14, 255), properties::LineWidth(7), properties::LineStyle::LongDashed());
}

void testFastPlot()
{
    const size_t num_elements = 30;
    Vector<float> x(num_elements), y(num_elements);

    setCurrentElement("view_00");
    clearView();

    float t = 0.0;

    for (size_t k = 0; k < num_elements; k++)
    {
        x(k) = 10.0 * cos(t) + 20.0;
        y(k) = 10.0 * sin(t) + 20.0 + k;

        t = t + 0.3;
    }

    axis({0.0, 16.0, -1.0}, {50.0, 64.0, 1.0});
    fastPlot(x + 3.0f, y, properties::Color(0, 255, 255));
    fastPlot(x + 4.0f, y, properties::Color(212, 14, 55));
    fastPlot(x + 5.0f, y, properties::Color(212, 255, 55));
    fastPlot(x + 6.0f, y, properties::Color(212, 14, 255));

    setCurrentElement("view_02");
    clearView();
    t = 0.0;
    x.resize(num_elements * 10);
    y.resize(num_elements * 10);

    for (size_t k = 0; k < (num_elements * 10); k++)
    {
        x(k) = 10.0f * cos(t) + 20.0f;
        y(k) = 10.0f * sin(t) + 20.0f + static_cast<float>(k) / 10.0f;

        t = t + 0.03;
    }

    axis({0.0, 16.0, -1.0}, {50.0, 64.0, 1.0});
    fastPlot(x + 3.0f, y, properties::Color(0, 255, 255));
    fastPlot(x + 4.0f, y, properties::Color(212, 14, 55));
    fastPlot(x + 5.0f, y, properties::Color(212, 255, 55));
    fastPlot(x + 6.0f, y, properties::Color(212, 14, 255));
}

void testLineCollection()
{
    const size_t num_lines = 5;
    Vector<float> x(num_lines * 2), y(num_lines * 2);

    setCurrentElement("view_00");
    clearView();

    float t = 0.0f;

    size_t idx = 0;

    for (size_t k = 0; k < num_lines; k++)
    {
        x(idx) = t * 2.0f;
        y(idx) = t * 2.0f;

        x(idx + 1) = t * 2.0f + cos(t);
        y(idx + 1) = t * 2.0f + sin(t);

        idx += 2;

        t = t + 0.3;
    }

    axis({0.0, 0.0, -1.0}, {10.0, 10.0, 1.0});
    lineCollection(x, y, properties::Color(255, 0, 0));
}

void testLineCollection3()
{
    const size_t num_lines = 5;
    Vector<float> x(num_lines * 2), y(num_lines * 2), z(num_lines * 2);

    setCurrentElement("view_00");
    clearView();

    float t = 0.0f;

    size_t idx = 0;

    for (size_t k = 0; k < num_lines; k++)
    {
        x(idx) = t * 2.0f;
        y(idx) = t * 2.0f;
        z(idx) = t * 2.0f;

        x(idx + 1) = t * 2.0f + cos(t);
        y(idx + 1) = t * 2.0f + sin(t);
        z(idx + 1) = t * 2.0f + sin(t) + cos(t);

        idx += 2;

        t = t + 0.3;
    }

    axis({0.0, 0.0, -1.0}, {10.0, 10.0, 10.0});
    lineCollection3(x, y, z, properties::Color(255, 0, 0));
}

void testStem()
{
    const size_t num_elements = 30;

    const Vector<float> x = linspaceFromBoundariesAndCount<float>(0.0f, 5.0f, num_elements);
    const Vector<float> y = dvs::sin(x);

    setCurrentElement("view_00");
    clearView();

    axis({0.0, -1.0, -1.0}, {5.0, 5.0, 1.0});
    stem(x, y, properties::Color::Red());
}

void testStairs()
{
    const size_t num_elements = 30;
    Vector<float> xf(num_elements), yf(num_elements);

    double t = 0.0;

    for (size_t k = 0; k < num_elements; k++)
    {
        xf(k) = t;
        yf(k) = 10.0 * sin(t) + 20.0 + k;

        t = t + 0.3;
    }

    setCurrentElement("view_00");
    clearView();

    stairs(xf, yf, properties::Color(21, 14, 55), properties::LineWidth(2));
    plot(xf, yf, properties::Color(21, 14, 255), properties::LineWidth(2));
    scatter(xf, yf, properties::Color(255, 0, 0), properties::PointSize(10));
}

void testPlot3()
{
    const size_t num_elements = 30;
    Vector<double> x(num_elements), y(num_elements), z(num_elements);
    Vector<float> xf(num_elements), yf(num_elements), zf(num_elements);

    double t = 0.0;

    for (size_t k = 0; k < num_elements; k++)
    {
        xf(k) = 1.0 * cos(t) + 0.0;
        yf(k) = 1.0 * sin(t) + 0.0;
        zf(k) = t;

        x(k) = xf(k);
        y(k) = yf(k);
        z(k) = t;
        t = t + 0.3;
    }

    setCurrentElement("view_00");
    clearView();

    plot3(x, y, z, properties::Color(212, 14, 55), properties::LineWidth(1));
    plot3(xf + 0.1f, yf, zf, properties::Color(21, 14, 55), properties::LineWidth(7));
}

void testFastPlot3()
{
    const size_t num_elements = 30;
    Vector<double> x(num_elements), y(num_elements), z(num_elements);
    Vector<float> xf(num_elements), yf(num_elements), zf(num_elements);

    double t = 0.0;

    for (size_t k = 0; k < num_elements; k++)
    {
        xf(k) = 1.0 * cos(t) + 0.0;
        yf(k) = 1.0 * sin(t) + 0.0;
        zf(k) = t;

        x(k) = xf(k);
        y(k) = yf(k);
        z(k) = t;
        t = t + 0.3;
    }

    setCurrentElement("view_00");
    clearView();

    fastPlot3(x, y, z, properties::Color(212, 14, 55));
    fastPlot3(xf + 0.1f, yf, zf, properties::Color(21, 14, 55));
}

void testImShow()
{
    const uint32_t num_rows = 800, num_cols = 800;
    ImageC3<float> img3(num_rows, num_cols);
    ImageC1<float> img1(num_rows, num_cols);
    // const double max_val = num_rows * num_cols;

    for (uint32_t r = 0; r < num_rows; r++)
    {
        for (uint32_t c = 0; c < num_cols; c++)
        {
            const float xr = 3.0f * (static_cast<float>(c) - 300.5f) / 800.0f;
            const float yr = 3.0f * (static_cast<float>(r) - 400.5f) / 800.0f;
            const float rr = std::sqrt(xr * xr + yr * yr);

            const float xg = 2.0f * (static_cast<float>(c) - 500.5f) / 800.0f;
            const float yg = 2.0f * (static_cast<float>(r) - 350.5f) / 800.0f;
            const float rg = std::sqrt(xg * xg + yg * yg);

            const float xb = 4.0f * (static_cast<float>(c) - 200.5f) / 800.0f;
            const float yb = 4.0f * (static_cast<float>(r) - 600.5f) / 800.0f;
            const float rb = std::sqrt(xb * xb + yb * yb);

            img3(r, c, 0) = (std::sin(rb) / rr + 1.0f) * 0.5f;
            img3(r, c, 1) = (std::sin(rb) / rg + 1.0f) * 0.5f;
            img3(r, c, 2) = (std::sin(rb) / rb + 1.0f) * 0.5f;

            img1(r, c) = (std::sin(rb) / rr + 1.0f) * 0.5f;

            // img(r, c, 0) = (r * c) / max_val;
            // img(r, c, 1) = 1.0f - (r * c) / max_val;
            // img(r, c, 2) = (r * (num_cols - 1 - c)) / max_val;
        }
    }
    setCurrentElement("view_00");
    clearView();
    imShow(img3, properties::Alpha(137));

    setCurrentElement("view_01");
    imShow(img1, properties::Alpha(137));
}

void testAxis()
{
    setCurrentElement("view_00");
    clearView();

    axis({1.0, 2.5}, {7.2, 8.4});

    setCurrentElement("view_01");
    clearView();

    axis({-1.0, 1.5, 3.4}, {5.4, 9.2, 5.5});
}

void testLegend()
{
    const int num_rows = 20, num_cols = 25;
    Matrix<double> x(num_rows, num_cols), y(num_rows, num_cols), z(num_rows, num_cols);

    double inc = 0.4;
    for (int r = 0; r < num_rows; r++)
    {
        for (int c = 0; c < num_cols; c++)
        {
            const double rd = static_cast<double>(r - 5) * inc;
            const double cd = static_cast<double>(c - 5) * inc * 2;
            x(r, c) = c;
            y(r, c) = r;
            z(r, c) = std::sin(std::sqrt(rd * rd + cd * cd));
        }
    }

    const size_t num_elements = 30;
    Vector<float> x0(num_elements), y0(num_elements);
    Vector<float> x1(num_elements), y1(num_elements);
    Vector<float> x2(num_elements), y2(num_elements);

    double t = 0.0;

    for (size_t k = 0; k < num_elements; k++)
    {
        x0(k) = 10.0 * cos(t);
        y0(k) = 10.0 * sin(t) + k;

        t = t + 0.3;
    }

    x1 = x0 * 2.0f;
    y1 = y0 * 2.0f;

    x2 = x0 * 3.0f;
    y2 = y0 * 3.0f;

    setCurrentElement("view_00");
    clearView();

    axis({-32.0, 0.0, -2.0}, {32.0, 110.0, 2.0});
    plot(x0, y0, properties::Color(212, 14, 55), properties::Name("AAAaaaBBBbbb"));
    plot(x1, y1, properties::Color(12, 255, 55), properties::Name("sig0"));
    plot(x2, y2, properties::Color(127, 14, 255), properties::Name("ej0293e2?rq430#€pqigj"));
    surf(x, y, z, properties::EdgeColor(0, 255, 0), properties::FaceColor(255, 0, 0), properties::Name("SURF"));
    surf(
        x, y, z + 1.0, properties::EdgeColor(0, 0, 0), properties::ColorMap::Jet(), properties::Name("SURF_COLOR_MAP"));
    showLegend();

    setCurrentElement("view_01");
    clearView();

    axis({-32.0, 0.0, -2.0}, {32.0, 110.0, 2.0});
    plot(x0, y0, properties::Color(212, 14, 55), properties::Name("AAAaaaBBBbbb"));
    plot(x1, y1, properties::Color(12, 255, 55), properties::Name("sig0"));
    plot(x2, y2, properties::Color(127, 14, 255), properties::Name("ej0293e2?rq430#€pqigj"));
    surf(x, y, z, properties::EdgeColor(0, 255, 0), properties::FaceColor(255, 0, 0), properties::Name("SURF"));
    surf(
        x, y, z + 1.0, properties::EdgeColor(0, 0, 0), properties::ColorMap::Jet(), properties::Name("SURF_COLOR_MAP"));
    showLegend();
}

void testDrawTiles()
{
    const int num_rows = 20, num_cols = 25;
    Matrix<float> x(num_rows, num_cols), y(num_rows, num_cols), z(num_rows, num_cols);

    double inc = 0.4;
    for (int r = 0; r < num_rows; r++)
    {
        for (int c = 0; c < num_cols; c++)
        {
            const double rd = static_cast<double>(r - 5) * inc;
            const double cd = static_cast<double>(c - 5) * inc * 2;
            x(r, c) = c;
            y(r, c) = r;
            z(r, c) = 50.0 * std::sin(std::sqrt(rd * rd + cd * cd));
        }
    }

    const Vec2d tile_size(0.1, 0.2);

    setCurrentElement("view_00");
    clearView();

    drawTiles(z, tile_size, properties::EdgeColor(0, 0, 0), properties::FaceColor(12, 244, 244));
}

void testDrawMesh()
{
    using tp = double;

    Vector<Point3<tp>> vertices(12);
    vertices(0) = Point3<tp>(0.0, 0.0, 0.0);
    vertices(1) = Point3<tp>(1.0, 0.0, 0.0);
    vertices(2) = Point3<tp>(0.5, -1.0, 1.0);

    vertices(3) = Point3<tp>(0.0, 0.0, 0.0);
    vertices(4) = Point3<tp>(-1.0, 0.0, 0.0);
    vertices(5) = Point3<tp>(0.0, 1.0, 1.0);

    vertices(6) = Point3<tp>(0.0, 0.0, 0.0);
    vertices(7) = Point3<tp>(-1.0, 0.0, 0.0);
    vertices(8) = Point3<tp>(0.0, 1.0, -1.0);

    vertices(9) = Point3<tp>(0.0, 0.0, 0.0);
    vertices(10) = Point3<tp>(1.0, 0.0, 0.0);
    vertices(11) = Point3<tp>(0.5, -1.0, -1.0);

    Vector<IndexTriplet> indices(4);
    indices(0) = IndexTriplet(0, 1, 2);
    indices(1) = IndexTriplet(3, 4, 5);
    indices(2) = IndexTriplet(6, 7, 8);
    indices(3) = IndexTriplet(9, 10, 11);

    Vector<tp> x(12), y(12), z(12);

    for (size_t k = 0; k < x.size(); k++)
    {
        x(k) = vertices(k).x;
        y(k) = vertices(k).y;
        z(k) = vertices(k).z + 2.0;
    }

    setCurrentElement("view_00");
    clearView();

    axis({-2.0, -2.0, -2.0}, {2.0, 2.0, 2.0});

    drawMesh(vertices, indices, properties::EdgeColor(0, 0, 0), properties::FaceColor(12, 244, 244));
    drawMesh(x, y, z, indices, properties::EdgeColor(0, 0, 0), properties::FaceColor(255, 0, 244));
}

void testDrawArrow()
{
    using tp = double;

    Point2<tp> p(0.1, 0.2);
    Vec2<tp> v(0.5, -0.3);

    setCurrentElement("view_00");
    clearView();

    axis({-2.0, -2.0, -2.0}, {2.0, 2.0, 2.0});

    drawArrow(p, v, properties::Color(12, 14, 244));
}

void testQuiver()
{
    using tp = float;
    const size_t num_rows = 100, num_cols = 100;

    Matrix<tp> x, y, u, v;

    const std::pair<Matrix<tp>, Matrix<tp>> mesh_grid = meshGrid(0.1, 100.0, 0.1, 100.0, num_cols, num_rows);
    x = mesh_grid.first;
    y = mesh_grid.second;

    u = dvs::cos(x);
    v = dvs::sin(y);

    setCurrentElement("view_00");
    clearView();

    axis({-2.0, -2.0, -2.0}, {2.0, 2.0, 2.0});

    quiver(x, y, u, v, properties::Color(255, 0, 0));
}

void testDrawLine3D()
{
    using tp = double;

    Line3D<tp> line(Point3<tp>(0.0, 0.0, 0.0), Vec3<tp>(1.0, 1.0, 1.0));
    tp t0 = 0;
    tp t1 = 1.0;

    Vector<double> x{VectorInitializer<double>{0.0, 1.0}};
    Vector<double> y{VectorInitializer<double>{0.0, 1.0}};
    Vector<double> z{VectorInitializer<double>{0.0, 1.0}};

    setCurrentElement("view_00");
    clearView();

    axis({-2.0, -2.0, -2.0}, {2.0, 2.0, 2.0});

    drawLine(line, t0, t1, properties::Color(12, 244, 244));
    scatter3(x, y, z, properties::Color(0, 0, 0), properties::PointSize(3));
}

void testDrawLine2D()
{
    using tp = double;

    ParametricLine2D<tp> line(Point2<tp>(0.0, 0.0), Vec2<tp>(1.0, 1.0));
    HomogeneousLine2D<tp> line_h(0.1, 0.2, 0.3);
    tp t0 = 0;
    tp t1 = 1.0;

    Vector<double> x{VectorInitializer<double>{0.0, 1.0}};
    Vector<double> y{VectorInitializer<double>{0.0, 1.0}};
    Vector<double> z{VectorInitializer<double>{0.0, 0.0}};

    setCurrentElement("view_00");
    clearView();

    axis({-2.0, -2.0, -2.0}, {2.0, 2.0, 2.0});

    drawLine2D(line, t0, t1, properties::Color(12, 244, 244));
    drawLine2DBetweenXValues(line_h, -3.0, 3.0, properties::Color(12, 15, 244));
    drawLine2DBetweenYValues(line_h, -2.0, 2.0, properties::Color(12, 15, 244));
    scatter3(x, y, z, properties::Color(0, 0, 0), properties::PointSize(3));
}

void testDrawLineBetweenPoints()
{
    using tp = double;

    Point3<tp> p0(0.1, 0.2, 0.2);
    Point3<tp> p1(2.0, 1.0, 1.0);

    Vector<double> x{VectorInitializer{p0.x, p1.x}};
    Vector<double> y{VectorInitializer{p0.y, p1.y}};
    Vector<double> z{VectorInitializer{p0.z, p1.z}};

    setCurrentElement("view_00");
    clearView();

    axis({-2.0, -2.0, -2.0}, {2.0, 2.0, 2.0});

    drawLineBetweenPoints(p0, p1, properties::Color(12, 244, 0));
    scatter3(x, y, z, properties::Color(0, 0, 0), properties::PointSize(3));
}

#endif  // TEST_APPLICATIONS_BASIC_TESTS_CPP_TESTS_H_
