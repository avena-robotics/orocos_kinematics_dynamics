//Copyright  (C)  2007  Ruben Smits <ruben dot smits at intermodalics dot eu>
//
//Version: 1.0
//Author: Ruben Smits Ruben Smits <ruben dot smits at intermodalics dot eu>
//Author: Zihan Chen <zihan dot chen dot jhu at gmail dot com>
//Author: Matthijs van der Burgh <MatthijsBurgh at outlook dot com>
//Maintainer: Ruben Smits Ruben Smits <ruben dot smits at intermodalics dot eu>
//Maintainer: Matthijs van der Burgh <MatthijsBurgh at outlook dot com>
//URL: http://www.orocos.org/kdl
//
//This library is free software; you can redistribute it and/or
//modify it under the terms of the GNU Lesser General Public
//License as published by the Free Software Foundation; either
//version 2.1 of the License, or (at your option) any later version.
//
//This library is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//Lesser General Public License for more details.
//
//You should have received a copy of the GNU Lesser General Public
//License along with this library; if not, write to the Free Software
//Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


#include <kdl/path.hpp>
#include <kdl/path_line.hpp>
#include <kdl/rotational_interpolation_sa.hpp>
#include <kdl/velocityprofile.hpp>
#include <kdl/velocityprofile_trap.hpp>
#include <kdl/trajectory.hpp>
#include <kdl/trajectory_segment.hpp>
#include "PyKDL.h"

namespace py = pybind11;
using namespace KDL;


void init_motion(py::module &m)
{

    // --------------------
    // RotationalInterpolation
    // --------------------
    py::class_<RotationalInterpolation>(m, "RotationalInterpolation");

    // --------------------
    // RotationalInterpolation_SingleAxis
    // --------------------
    py::class_<RotationalInterpolation_SingleAxis, RotationalInterpolation>(m, "RotationalInterpolation_SingleAxis")
    .def(py::init<>());


    // --------------------
    // Path
    // --------------------
    py::class_<Path>(m, "Path");

    // --------------------
    // Path_Line
    // --------------------
    py::class_<Path_Line, Path>(m, "Path_Line")
    .def(py::init<const Frame&, const Frame&, RotationalInterpolation*, double, bool>())
    .def("PathLength", &Path_Line::PathLength)
    .def("Pos", &Path_Line::Pos, py::arg("s"))
    .def("LengthToS", &Path_Line::LengthToS, py::arg("length"));

    // --------------------
    // VelocityProfile
    // --------------------
    py::class_<VelocityProfile>(m, "VelocityProfile");

    // --------------------
    // VelocityProfile_Trap
    // --------------------
    py::class_<VelocityProfile_Trap, VelocityProfile>(m, "VelocityProfile_Trap")
    .def(py::init<double, double>())
    .def("SetProfile", &VelocityProfile_Trap::SetProfile, py::arg("pos1"), py::arg("pos2"));

    // --------------------
    // Trajectory
    // --------------------
    py::class_<Trajectory>(m, "Trajectory");

    // --------------------
    // Trajectory_Segment
    // --------------------
    py::class_<Trajectory_Segment, Trajectory>(m, "Trajectory_Segment")
    .def("Pos", &Trajectory_Segment::Pos, py::arg("time"))
    .def("Vel", &Trajectory_Segment::Vel, py::arg("time"))
    .def("Acc", &Trajectory_Segment::Acc, py::arg("time"))
    .def("Duration", &Trajectory_Segment::Duration);

}