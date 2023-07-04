//Copyright  (C)  2023  Łukasz Łęcki <lukasz dot lecki at pomagier dot info>

#include <kdl/path.hpp>
#include <kdl/path_line.hpp>
#include <kdl/path_point.hpp>
#include <kdl/path_composite.hpp>
#include <kdl/path_roundedcomposite.hpp>
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
    // Path_Point
    // --------------------
    py::class_<Path_Point, Path>(m, "Path_Point")
    .def(py::init<const Frame&>())
    .def("Pos", &Path_Point::Pos, py::arg("s"))
    .def("Vel", &Path_Point::Vel, py::arg("s"), py::arg("sd"))
    .def("Acc", &Path_Point::Acc, py::arg("s"), py::arg("sd"), py::arg("sdd"))
    .def("PathLength", &Path_Point::PathLength)
    .def("LengthToS", &Path_Point::LengthToS, py::arg("length"));

    // --------------------
    // Path_Composite
    // --------------------
    py::class_<Path_Composite, Path>(m, "Path_Composite")
    .def(py::init<>());

    // --------------------
    // Path_RoundedComposite
    // --------------------
    py::class_<Path_RoundedComposite, Path>(m, "Path_RoundedComposite")
    .def(py::init<double, double, RotationalInterpolation*, bool>());

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