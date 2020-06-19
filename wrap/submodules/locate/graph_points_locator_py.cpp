/* Copyright (C) 2020 Pablo Hernandez-Cerdan
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "pybind11_common.h"
#include "sglocate_common.h"

#include "graph_points_locator.hpp"

#include <vtkIdList.h>
#include <vtkPoints.h>

namespace py = pybind11;
using namespace SG;

void init_graph_points_locator(py::module &m) {
    py::class_<IdWithGraphDescriptor, std::shared_ptr<IdWithGraphDescriptor>>(
            m, "id_with_graph_descriptor")
            .def(py::init<>())
            .def_readwrite("exist", &IdWithGraphDescriptor::exist)
            .def_readwrite("id", &IdWithGraphDescriptor::id, "id for vtk")
            .def_readwrite("descriptor", &IdWithGraphDescriptor::descriptor,
                           "descriptor of the graph");

    /* *********************************************************************/

    py::class_<vtkOctreePointLocator, vtkSmartPointer<vtkOctreePointLocator>>(
            m, "vtkOctreePointLocator")
            .def("__str__", [](vtkOctreePointLocator &p) {
                std::stringstream os;
                p.Print(os);
                return os.str();
            });

    py::class_<vtkIdList, vtkSmartPointer<vtkIdList>>(m, "vtkIdList")
            .def("__str__",
                 [](vtkIdList &id_list) {
                     std::stringstream os;
                     id_list.Print(os);
                     return os.str();
                 })
            .def("get_id", &vtkIdList::GetId)
            .def("insert_id", &vtkIdList::InsertId)
            .def("insert_next_id", &vtkIdList::InsertNextId)
            .def("is_id", &vtkIdList::IsId)
            .def("delete_id", &vtkIdList::DeleteId)
            .def("intersect_with",
                 [](vtkIdList &this_id_list, vtkIdList &other_id_list) {
                     return this_id_list.IntersectWith(other_id_list);
                 })
            .def("get_number_of_ids", &vtkIdList::GetNumberOfIds);

    /* *********************************************************************/

    m.def("build_octree_locator",
          [](const vtkSmartPointer<vtkPoints> &input_points) {
              return build_octree_locator(input_points.Get());
          });

    /* *********************************************************************/

    m.def(
            "closest_existing_descriptors_by_graph",
            [](const vtkSmartPointer<vtkIdList> &input_list,
               const std::unordered_map<vtkIdType,
                                        std::vector<graph_descriptor>> &idMap) {
                return closest_existing_descriptors_by_graph(input_list.Get(),
                                                             idMap);
            },
            R"(
The output is a vector (of size equal to the number of graphs on input idMap)
where each index is associated to a graph, and it contains a graph_descriptor
and a point id, corresponding to the closest EXISTING point for that graph.

Given an ordered list, return a list with graph_descriptors and point id.
The order of filling is given by the the order of the input list.
The size of the return vector is given by the number of graphs existing in
idMap.

returns a vector of id_with_graph_descriptor

Parameters:
----------
input_list: vtkIdList
    vtkIdList generated by

id_map: dict(vtkIdType, [graph_descriptor])
          )",
            py::arg("input_list"), py::arg("id_map"));

    /* *********************************************************************/

    m.def(
            "closest_existing_vertex_by_graph",
            [](const vtkSmartPointer<vtkIdList> &input_list,
               const std::unordered_map<vtkIdType,
                                        std::vector<graph_descriptor>> &idMap) {
                return closest_existing_vertex_by_graph(input_list.Get(),
                                                        idMap);
            },
            R"(
Similar to closest_existing_descriptors_by_graph but returns the closest
vertex instead of just the closest existing vertex OR edge.

The output is a vector (of size equal to the number of graphs on input idMap)
where each index is associated to a graph, and it contains a graph_descriptor
and a point id, corresponding to the closest EXISTING point for that graph.

Given an ordered list, return a list with graph_descriptors and point id.
The order of filling is given by the the order of the input list.
The size of the return vector is given by the number of graphs existing in
idMap.

returns a vector of id_with_graph_descriptor

Parameters:
----------
input_list: vtkIdList
    vtkIdList generated by:
     graph_closest_n_points_locator,
     graph_closest_points_by_radius_locator

id_map: dict(vtkIdType, [graph_descriptor])
          )",
            py::arg("input_list"), py::arg("id_map"));

    /* *********************************************************************/

    m.def(
            "graph_closest_n_points_locator",
            [](const PointType &query_point,
               vtkSmartPointer<vtkOctreePointLocator> &octree_ptr,
               const std::unordered_map<vtkIdType,
                                        std::vector<graph_descriptor>> &idMap,
               const int closest_n_points) {
                return graph_closest_n_points_locator(
                        query_point, octree_ptr.Get(), idMap, closest_n_points);
            },
            R"(
Use the octree point locator and the idMap from a set of graphs to query a
point in space. It returns a list of vtkId points

Parameters:
----------
query_point: PointType
octree: vtkOctreePointLocator
id_map: dict(vtkIdType, [graph_descriptor])
closest_n_points: int
    number of closest points to return
            )",
            py::arg("query_point"), py::arg("octree"), py::arg("id_map"),
            py::arg("number_of_points") = 5);

    /* *********************************************************************/

    m.def(
            "graph_closest_points_by_radius_locator",
            [](const PointType &query_point,
               vtkSmartPointer<vtkOctreePointLocator> &octree_ptr,
               const std::unordered_map<vtkIdType,
                                        std::vector<graph_descriptor>> &idMap,
               double radius) {
                return graph_closest_points_by_radius_locator(
                        query_point, octree_ptr.Get(), idMap, radius);
            },
            R"(
Use the octree point locator and the idMap from a set of graphs to query a
point in space. It returns a list of vtkId points

Parameters:
----------
query_point: PointType
octree: vtkOctreePointLocator
id_map: dict(vtkIdType, [graph_descriptor])
radius: float
    return all points within radius
            )",
            py::arg("query_point"), py::arg("octree"), py::arg("id_map"),
            py::arg("radius"));
}
