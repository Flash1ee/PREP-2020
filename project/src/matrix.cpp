#include "matrix.h"

#include <iostream>
#include <iterator>

#include "exceptions.h"

namespace prep {
Matrix::Matrix(size_t rows, size_t cols)
    : m_rows(rows), m_cols(cols), m_data(rows) {

    for (auto& row : m_data) {
        row.resize(m_cols);
    }
}
Matrix::Matrix(std::istream& is) {
    is >> m_rows >> m_cols;
    if (!is) {
        throw InvalidMatrixStream();
    }
    m_data.resize(m_rows);

    for (auto& row : m_data) {
        row.resize(m_cols);
        for (auto& el : row) {
            is >> el;
            if (!is) {
                throw InvalidMatrixStream();
            }
        }
    }
}
size_t Matrix::getRows() const {
    return m_rows;
}
size_t Matrix::getCols() const {
    return m_cols;
}
double& Matrix::get(size_t i, size_t j) {
    if (i >= m_rows || j >= m_cols) {
        throw OutOfRange(i, j, *this);
    }
    return m_data[i][j];
}
double Matrix::get(size_t i, size_t j) const {
    if (i >= m_rows || j >= m_cols) {
        throw OutOfRange(i, j, *this);
    }
    return m_data[i][j];
}

double Matrix::operator()(size_t i, size_t j) const {
    return this->get(i, j);
}
double& Matrix::operator()(size_t i, size_t j) {
    return this->get(i, j);
}
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    auto formatter = std::numeric_limits<double>::max_digits10;
    os << matrix.m_rows << " " << matrix.m_cols << std::endl;

    for (size_t i = 0; i < matrix.m_rows; ++i) {
        for (size_t j = 0; j < matrix.m_cols; ++j) {
            os << std::setprecision(formatter) << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}
bool Matrix::operator==(const Matrix& rhs) const {
    if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols) {
        return false;
    }
    auto eps = 1e-07;
    for (size_t i = 0; i < this->m_rows; ++i) {
        for (size_t j = 0; j < this->m_cols; ++j) {
            if (std::fabs(rhs(i, j) - this->get(i, j)) > eps) {
                return false;
            }
        }
    }
    return true;
}
bool Matrix::operator!=(const Matrix& rhs) const {
    return !(*this == rhs);
}
Matrix Matrix::operator+(const Matrix& rhs) const {
    if (this->m_cols != rhs.m_cols || this->m_rows != rhs.m_rows) {
        throw DimensionMismatch(rhs);
    }
    if (!this->m_rows || !this->m_cols || !rhs.m_rows || !rhs.m_cols) {
        throw DimensionMismatch(rhs);
    }
    Matrix res(this->m_rows, this->m_cols);
    for (size_t i = 0; i < this->m_rows; ++i) {
        for (size_t j = 0; j < this->m_cols; ++j) {
            res(i, j) = this->get(i, j) + rhs(i, j);
        }
    }
    return res;
}
Matrix Matrix::operator-(const Matrix& rhs) const {
    if (this->m_cols != rhs.m_cols || this->m_rows != rhs.m_rows) {
        throw DimensionMismatch(rhs);
    }
    if (!this->m_rows || !this->m_cols || !rhs.m_rows || !rhs.m_cols) {
        throw DimensionMismatch(rhs);
    }
    Matrix res(this->m_rows, this->m_cols);
    for (size_t i = 0; i < this->m_rows; ++i) {
        for (size_t j = 0; j < this->m_cols; ++j) {
            res(i, j) = this->get(i, j) - rhs(i, j);
        }
    }
    return res;
}
Matrix Matrix::operator*(const Matrix& rhs) const {
    if (!this->m_rows || !this->m_cols || !rhs.m_rows || !rhs.m_cols) {
        throw DimensionMismatch(rhs);
    }
    if (this->m_cols != rhs.m_rows) {
        throw DimensionMismatch(rhs);
    }
    Matrix res(this->m_rows, rhs.m_cols);

    for (size_t i = 0; i < this->m_rows; ++i) {
        for (size_t j = 0; j < rhs.m_cols; ++j) {
            for (size_t k = 0; k < this->m_cols; ++k) {
                res(i, j) += this->get(i, k) * rhs(k, j);
            }
        }
    }
    return res;
}
Matrix Matrix::transp() const {
    Matrix res(this->m_cols, this->m_rows);

    for (size_t i = 0; i < res.m_rows; ++i) {
        for (size_t j = 0; j < res.m_cols; ++j) {
            res(i, j) = this->get(j, i);
        }
    }

    return res;
}
Matrix Matrix::operator*(double val) const {
    Matrix res(this->m_rows, this->m_cols);

    for (size_t i = 0; i < this->m_rows; ++i) {
        for (size_t j = 0; j < this->m_cols; ++j) {
            res(i, j) = this->get(i, j) * val;
        }
    }
    return res;
}
Matrix operator*(double val, const Matrix& matrix) {
    Matrix res(matrix.m_rows, matrix.m_cols);
    for (size_t i = 0; i < matrix.m_rows; ++i) {
        for (size_t j = 0; j < matrix.m_cols; ++j) {
            res(i, j) = val * matrix(i, j);
        }
    }
    return res;
}
static void get_minor(const Matrix& src, Matrix& tmp, size_t cur_col, size_t cur_row) {
    size_t dst_rows, dst_cols;
    dst_rows = dst_cols = 0;
    for (size_t i = 0; i < src.getRows(); ++i) {
        if (i == cur_row) {
            continue;
        }
        dst_cols = 0;

        for (size_t j = 0; j < src.getCols(); ++j) {
            if (j != cur_col) {
                tmp(dst_rows, dst_cols) = src(i, j);
                dst_cols++;
            }
        }
        dst_rows++;
    }
}
double Matrix::det() const {
    double determinate = 0;
    if (m_cols < 1 || m_rows < 1 || m_cols != m_rows) {
        throw DimensionMismatch(*this);
    }
    if (m_rows == 1) {
        return this->get(0, 0);
    }
    if (m_rows == 2) {
        return this->get(0, 0) * this->get(1, 1) - this->get(1, 0) * this->get(0, 1);
    }
    for (size_t el = 0; el < m_cols; ++el) {
        Matrix tmp(m_rows - 1, m_cols - 1);

        get_minor(*this, tmp, el, 0);

        determinate += (pow(-1, el) * this->get(0, el) * tmp.det());
    }
    return determinate;
}

Matrix Matrix::adj() const {
    if (m_rows != m_cols || m_rows < 1) {
        throw DimensionMismatch(*this);
    }
    Matrix transponse = transp();

    Matrix adjective(m_rows, m_cols);
    if (m_rows == 1) {
        adjective(0, 0) = this->get(0, 0);
        return adjective;
    }
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_cols; ++j) {
            Matrix tmp(m_rows - 1, m_cols - 1);

            get_minor(transponse, tmp, j, i);

            double determinate = tmp.det();

            adjective(i, j) = determinate * pow(-1, i + j);
        }
    }
    return adjective;
}
Matrix Matrix::inv() const {
    if (m_rows != m_cols || m_rows < 1) {
        throw DimensionMismatch(*this);
    }
    if (m_rows == 1) {
        Matrix invert(1, 1);
        if (!this->get(0, 0)) {
            throw SingularMatrix();
        }
        invert(0, 0) = 1 / this->get(0, 0);

        return invert;
    }

    Matrix adjective = adj();
    auto eps = 1e-7;
    double determinate = det();
    if (std::fabs(determinate) <= eps) {
        throw SingularMatrix();
    }

    Matrix invert = adjective * (1 / determinate);

    return invert;
}
}  // namespace prep
