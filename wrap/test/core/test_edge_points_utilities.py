"""
Copyright (C) 2020 Pablo Hernande-Cerdan.

This file is part of SGEXT: http://github.com/phcerdan/sgext.

This file may be used under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation and appearing in
the file LICENSE.GPL included in the packaging of this file.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""

from sgext import core
import unittest

class TestEdgePointsUtilities(unittest.TestCase):
    def test_edge_points_length(self):
        se = core.spatial_edge()
        se.edge_points = [[0,0,0], [1,0,0]]
        contour = core.edge_points_length(se)
        self.assertGreaterEqual(contour, 1)

    def test_ete_distance(self):
        graph = core.spatial_graph(2)
        sn = core.spatial_node()
        sn.pos = [1.0,1.0,1.0]
        graph.set_vertex(1, sn)
        [ed, added] = core.graph.add_edge(0,1,core.spatial_edge(), graph)
        ete_distance = core.ete_distance(ed, graph)
        self.assertGreaterEqual(ete_distance, 1)

    def test_contour_length(self):
        graph = core.spatial_graph(2)
        sn = core.spatial_node()
        sn.pos = [1.0,1.0,1.0]
        graph.set_vertex(1, sn)
        [ed, added] = core.graph.add_edge(0,1,core.spatial_edge(), graph)
        contour = core.contour_length(ed, graph)
        self.assertGreaterEqual(contour, 1)

    def test_insert_unique_edge_point_with_distance_order(self):
        point0 = [0,0,0]
        point1 = [1,0,0]
        point2 = [2,0,0]
        new_point = [3,0,0]
        point_container = [point0, point1, point2]
        new_point_container = core.insert_unique_edge_point_with_distance_order(
            point_container, new_point)
        self.assertEqual(len(point_container), 3)
        self.assertEqual(len(new_point_container), 4)

    def test_check_edge_points_are_contiguous(self):
        point0 = [0,0,0]
        point1 = [1,0,0]
        point2 = [2,0,0]
        point_container = [point0, point1, point2]
        are_contiguous = core.check_edge_points_are_contiguous(point_container)
        self.assertTrue(are_contiguous)
        point5 = [0,0,5]
        point_container = [point0, point1, point2, point5]
        are_contiguous = core.check_edge_points_are_contiguous(point_container)
        self.assertFalse(are_contiguous)

if __name__ == '__main__':
    unittest.main()


