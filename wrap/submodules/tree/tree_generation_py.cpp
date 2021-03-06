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

#include "pybind11_common.h"

#include "tree_generation.hpp"

namespace py = pybind11;
using namespace SG;

void init_tree_generation(py::module &m) {

  py::class_<AnomalyParameters>(m, "AnomalyParameters",
R"(Parameters to mark nodes/edges as anomalies in tree_generation_visitor)")
    .def(py::init())
    .def_readwrite("num_edge_points_for_short",
        &AnomalyParameters::num_edge_points_for_short,
R"(Number of edge points to consider an edge short
Used for aneurysms for example -- depends heavily on data --
)")
    .def_readwrite("decrease_radius_ratio_factor", &AnomalyParameters::decrease_radius_ratio_factor,
R"(Radio (diameter) parameter. This factor is multiplied
with the tree_generation parameter:
decrease_radius_ratio_to_increase_generation, to mark it as an anomaly.
)")
    .def("__repr__", [](const AnomalyParameters &self) {
        std::stringstream os;
        SG::print(self, os);
        return os.str();
      });

    m.def("tree_generation", &tree_generation,
          R"(
Associate to each node of the graph a generation based on the branching of
the tree. Generation = 0 is associated to the root node. An end node of the
first branching will have generation 1.

Sometimes is not clear in a Y branching if both ends will get its generation
increased, or only one. The parameter
decrease_radius_ratio_to_increase_generation allows to fine tune this
behaviour. Those nodes that have a smaller radius would increase its
generation.

Returns a dictionary {int->int} vertex to generation.

Parameters:
----------
graph: GraphType
  input spatial graph to get the vertices/nodes

distance_map_image: FloatImageType
  distance map image

spatial_nodes_position_are_in_physical_space: Bool [False]
  node positions are in physical space (instead of default index space)

decrease_radius_ratio_to_increase_generation: Float
  controls when the generation of a node will be increased, based on the radius
  decrease between connected nodes.

keep_generation_if_angle_less_than: Float
  Do not increase generation for angles smaller than this (in degrees)

increase_generation_if_angle_greater_than: Float
  increase generation if the angle is greater than this value.  Angle analysis is used in a second
  pass analysis, and it only applies to the cases where the first pass (based
  on radius) generates at leat two branches with the same generation. It fails
  to increase the target branch generation, when one of the sibling branches
   (with same source) got its generation increased by the radius first pass.

num_of_edge_points_to_compute_angle: Int
  when computing angles between edges with same source,
  use the edge point number m_num_of_edge_points_to_compute_angle closer to
  source.  Warning: This is not an index, but a count.

input_roots: [Int] i.e [vertex_descriptor]
  Vector holding user specified root nodes. If empty, the algorithm takes
  as root the vertex with greatest radius (from the distance map), and
  runs only in the largest connected component of the graph.
  If multiple roots are provided, the algorithm will start visiting from them.
  Also, it will assume there are disconnected components in the graph, one for
  each root.

input_fixed_generation_map: Dict {int->int}
  Map provided by the user to fix the generation for certain nodes.
  The algorithm won't modify the generation on those vertex.
  Empty by default.

verbose: Bool [False]
  extra information at execution
)",
          py::arg("graph"), py::arg("distance_map_image"),
          py::arg("spatial_nodes_position_are_in_physical_space") = false,
          py::arg("decrease_radius_ratio_to_increase_generation") = 0.1,
          py::arg("keep_generation_if_angle_less_than") = 10,
          py::arg("increase_generation_if_angle_greater_than") = 30,
          py::arg("num_of_edge_points_to_compute_angle") = 5,
          py::arg("input_roots") = std::vector<GraphType::vertex_descriptor>(),
          py::arg("input_fixed_generation_map") = SG::VertexGenerationMap(),
          py::arg("anomaly_parameters") = SG::AnomalyParameters(),
          py::arg("verbose") = false);

    /*********************************************/

    const std::string read_write_vertex_to_generation_map_common_docs =
            R"(
Read/Write a CSV-like file containing a one-line header and two comma-separated values
with vertex_id and generation.
Example:
# vertex_id,  generation
4, 0
5, 1
12, 2
This map can be used in @ref tree_generation to fix those nodes, avoiding
that tree_generation modifies them.

)";
    const std::string read_vertex_to_generation_map_parameters_docs =
            R"(
Parameters:
----------
input_file: String/Path
 input filename where the map is stored. tree_generation generates these maps as output.
)";
    m.def("read_vertex_to_generation_map", &read_vertex_to_generation_map,
          (read_write_vertex_to_generation_map_common_docs +
           read_vertex_to_generation_map_parameters_docs)
                  .c_str(),
          py::arg("input_file"));

    const std::string write_vertex_to_generation_map_parameters_docs =
            R"(
Parameters:
----------
vertex_to_generation_map: Dict {int->int}
 Map/Dict containing vertex to generations.

output_file: String/Path
 Filename to write down the vertex_to_generation_map
)";
    m.def("write_vertex_to_generation_map", &write_vertex_to_generation_map,
          (read_write_vertex_to_generation_map_common_docs +
           write_vertex_to_generation_map_parameters_docs)
                  .c_str(),
          py::arg("vertex_to_generation_map"), py::arg("output_file"));
}
