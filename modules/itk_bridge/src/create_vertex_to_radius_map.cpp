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

#include "create_vertex_to_radius_map.hpp"

namespace SG {

// explicit instantiation
template VertexToRadiusMap create_vertex_to_radius_map<GraphType>(
        const typename FloatImageType::Pointer &distance_map_image,
        const GraphType &input_graph,
        const bool spatial_nodes_position_are_in_physical_space,
        const bool /*verbose*/);
} // end namespace SG
