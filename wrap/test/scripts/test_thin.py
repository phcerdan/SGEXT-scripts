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

import _sgext.scripts as scripts
import unittest
import os, tempfile

class TestThin(unittest.TestCase):
    def setUp(self):
        # Create temp directory
        self.test_dir = tempfile.mkdtemp()
        dirname = os.path.dirname(os.path.abspath(__file__))
        self.input = os.path.join(dirname, '../../../images/bX3D.tif')
        if not os.path.exists(self.input):
            raise "Input image for test thin script not found: " + self.input

    def test_thin(self):
        scripts.thin(input=self.input,
                     out_foldername=self.test_dir,
                     foreground="black",
                     skel_type="end", select_type="first",
                     persistence=2,
                     visualize=False,
                     verbose=True)
