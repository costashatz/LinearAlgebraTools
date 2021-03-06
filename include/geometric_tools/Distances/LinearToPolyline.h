/**
Copyright (c) 2014, Konstantinos Chatzilygeroudis
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
    in the documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef GEOMETRIC_TOOLS_DISTANCES_LINEAR_TO_POLYLINE_H
#define GEOMETRIC_TOOLS_DISTANCES_LINEAR_TO_POLYLINE_H

/**
* Includes
**/
#include <geometric_tools/Math/Vector.h>
#include <geometric_tools/Primitives/LinearShapes.h>
#include <geometric_tools/Distances/2D/PointToPolyline.h>
#include <geometric_tools/Distances/LinearToLinear.h>
#include <geometric_tools/Primitives/Polyline.h>

namespace GeometricTools {

using Math::Vector;
using Primitives::Line;
using Primitives::Ray;
using Primitives::Segment;
using Primitives::Polyline;

namespace Distances {


/**
* Computes Segment to Polyline Distance Squared
* @param segment
* @param polyline
**/
template<unsigned int N>
double distanceSq(const Segment<N>& seg, const Polyline<N>& polyline)
{
    double m = std::numeric_limits<double>::infinity();
    for(unsigned int i=0;i<polyline.vertices().size()-1;i++)
    {
        double tmp = distanceSq(seg, Segment<N>(polyline.vertices()[i], polyline.vertices()[i+1]));
        if(tmp<m)
            m = tmp;
    }
    return m;
}

template<unsigned int N>
double distanceSq(const Polyline<N>& polyline, const Segment<N>& seg)
{
    return distanceSq(seg, polyline);
}


/**
* Computes Segment to Polyline Distance
* @param segment
* @param polyline
**/
template<unsigned int N>
double distance(const Segment<N>& seg, const Polyline<N>& polyline)
{
    return sqrt(distanceSq(seg,polyline));
}

template<unsigned int N>
double distance(const Polyline<N>& polyline, const Segment<N>& seg)
{
    return distance(seg, polyline);
}

} }

#endif
