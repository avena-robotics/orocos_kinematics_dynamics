//Copyright  (C)  2023  Łukasz Łęcki <lukasz dot lecki at pomagier dot info>

#include <kdl/path.hpp>
#include <kdl/path_line.hpp>
#include <kdl/path_point.hpp>
#include <kdl/path_composite.hpp>
#include <kdl/path_roundedcomposite.hpp>
#include <kdl/rotational_interpolation_sa.hpp>
#include <kdl/velocityprofile.hpp>
#include <kdl/velocityprofile_trap.hpp>
#include <kdl/velocityprofile_traphalf.hpp>
#include <kdl/velocityprofile_spline.hpp>
#include <kdl/trajectory.hpp>
#include <kdl/trajectory_segment.hpp>
#include <kdl/trajectory_composite.hpp>
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
    .def(py::init<>())
    .def("__copy__", [](const RotationalInterpolation_SingleAxis& self)
    {
        return RotationalInterpolation_SingleAxis(self);
    });


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
    .def(py::init<>())
    .def("PathLength", &Path_Composite::PathLength)
    .def("Add", &Path_Composite::Add, py::arg("geom"), py::arg("aggregate"));

    // --------------------
    // Path_RoundedComposite
    // --------------------
    py::class_<Path_RoundedComposite, Path>(m, "Path_RoundedComposite")
    .def(py::init<double, double, RotationalInterpolation*, bool>())
    .def("PathLength", &Path_RoundedComposite::PathLength)
    .def("Finish", &Path_RoundedComposite::Finish)
    .def("Add", &Path_RoundedComposite::Add, py::arg("F_base_point"));

    // --------------------
    // VelocityProfile
    // --------------------
    py::class_<VelocityProfile>(m, "VelocityProfile");

    // --------------------
    // VelocityProfile_Trap
    // --------------------
    py::class_<VelocityProfile_Trap, VelocityProfile>(m, "VelocityProfile_Trap")
    .def(py::init<double, double>())
    .def("SetProfile", &VelocityProfile_Trap::SetProfile, py::arg("pos1"), py::arg("pos2"))
    .def("SetProfileDuration", &VelocityProfile_Trap::SetProfileDuration, py::arg("pos1"), py::arg("pos2"), py::arg("newduration"))
    .def("SetProfileVelocity", &VelocityProfile_Trap::SetProfileVelocity, py::arg("pos1"), py::arg("pos2"), py::arg("newvelocity"))
    .def("Pos", &VelocityProfile_Trap::Pos, py::arg("time"))
    .def("Vel", &VelocityProfile_Trap::Vel, py::arg("time"))
    .def("Acc", &VelocityProfile_Trap::Acc, py::arg("time"))
    .def("Duration", &VelocityProfile_Trap::Duration);

    // --------------------
    // VelocityProfile_TrapHalf
    // --------------------
    py::class_<VelocityProfile_TrapHalf, VelocityProfile>(m, "VelocityProfile_TrapHalf")
    .def(py::init<double, double, bool>())
    .def("SetProfile", &VelocityProfile_TrapHalf::SetProfile, py::arg("pos1"), py::arg("pos2"))
    .def("SetProfileDuration", &VelocityProfile_TrapHalf::SetProfileDuration, py::arg("pos1"), py::arg("pos2"), py::arg("newduration"))
    .def("Pos", &VelocityProfile_TrapHalf::Pos, py::arg("time"))
    .def("Vel", &VelocityProfile_TrapHalf::Vel, py::arg("time"))
    .def("Acc", &VelocityProfile_TrapHalf::Acc, py::arg("time"))
    .def("Duration", &VelocityProfile_TrapHalf::Duration);

    // --------------------
    // VelocityProfile_Spline 
    // --------------------
    py::class_<VelocityProfile_Spline, VelocityProfile>(m, "VelocityProfile_Spline")
    .def(py::init<>())
    .def("SetProfile", &VelocityProfile_Spline::SetProfile, py::arg("pos1"), py::arg("pos2"))
    .def("SetProfileDuration", (void (VelocityProfile_Spline::*)(double, double, double)) &VelocityProfile_Spline::SetProfileDuration)
    .def("SetProfileDuration", (void (VelocityProfile_Spline::*)(double, double, double, double, double)) &VelocityProfile_Spline::SetProfileDuration)
    .def("SetProfileDuration", (void (VelocityProfile_Spline::*)(double, double, double, double, double, double, double)) &VelocityProfile_Spline::SetProfileDuration)
    .def("Pos", &VelocityProfile_Spline::Pos, py::arg("time"))
    .def("Vel", &VelocityProfile_Spline::Vel, py::arg("time"))
    .def("Acc", &VelocityProfile_Spline::Acc, py::arg("time"))
    .def("Duration", &VelocityProfile_Spline::Duration);

    // --------------------
    // Trajectory
    // --------------------
    py::class_<Trajectory>(m, "Trajectory");

    // --------------------
    // Trajectory_Segment
    // --------------------
    py::class_<Trajectory_Segment, Trajectory>(m, "Trajectory_Segment")
    .def(py::init<Path*, VelocityProfile*, bool>())
    .def("Pos", &Trajectory_Segment::Pos, py::arg("time"))
    .def("Vel", &Trajectory_Segment::Vel, py::arg("time"))
    .def("Acc", &Trajectory_Segment::Acc, py::arg("time"))
    .def("Duration", &Trajectory_Segment::Duration);

    // --------------------
    // Trajectory_Composite
    // --------------------
    py::class_<Trajectory_Composite, Trajectory>(m, "Trajectory_Composite")
    .def(py::init<>())
    .def("Duration", &Trajectory_Composite::Duration)
    .def("Add", &Trajectory_Composite::Add, py::arg("elem"));
}