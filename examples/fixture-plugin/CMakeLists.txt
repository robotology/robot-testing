# Robot Testing Framework
#
# Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA


cmake_minimum_required(VERSION 3.5)

find_package(RobotTestingFramework COMPONENTS DLL)

set(CMAKE_SHARED_MODULE_PREFIX "")

add_library(myfixture MODULE MyFixManager.cpp MyFixManager.h)
target_link_libraries(myfixture ${RobotTestingFramework_LIBRARIES})

add_executable(test test.cpp)
target_link_libraries(test ${RobotTestingFramework_LIBRARIES})
