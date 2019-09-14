/* ********************************************************************
 * Copyright (C) 2020 Pablo Hernandez-Cerdan.
 *
 * This file is part of SGEXT: http://github.com/phcerdan/sgext.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * *******************************************************************/

#include <pybind11/pybind11.h>

namespace py = pybind11;
void init_simulated_annealing_generator_parameters(py::module &);
void init_simulated_annealing_generator(py::module &);
void init_contour_length_generator(py::module &);

PYBIND11_MODULE(sggenerate, m) {
    m.doc() = "SGGenerate "; // optional module docstring
    init_simulated_annealing_generator_parameters(m);
    init_simulated_annealing_generator(m);
    init_contour_length_generator(m);
}
