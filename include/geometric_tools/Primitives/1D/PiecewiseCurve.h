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

#ifndef GEOMETRIC_TOOLS_PRIMITIVES_1D_PIECEWISE_CURVE_H
#define GEOMETRIC_TOOLS_PRIMITIVES_1D_PIECEWISE_CURVE_H

/**
* Includes
**/
#include <geometric_tools/Primitives/1D/Curve.h>

#include <geometric_tools/Math/Vector.h>
#include <geometric_tools/Math/Matrix.h>
#include <vector>

using std::vector;


namespace GeometricTools {

using Math::Matrix;
using Math::Vector;

namespace Primitives {

/**
* PiecewiseCurve Class
* Abstract 1D piecewise curve - base class for all 1D piecewise curves
**/
class PiecewiseCurve : public Curve
{
protected:
    vector<Curve*> curves_;
public:
    PiecewiseCurve() {}

    ~PiecewiseCurve()
    {
        for(unsigned int i=0;i<curves_.size();i++)
        {
            if(curves_[i])
                delete curves_[i];
        }
    }

    virtual vector<double> coeff()
    {
        if(curves_.size()==0)
            return vector<double>();
        vector<double> coef = curves_[0]->coeff();
        for(int i=1;i<curves_.size();i++)
        {
            auto tmp = curves_[i]->coeff();
            coef.insert(coef.end(), tmp.begin(), tmp.end());
        }
        return coef;
    }

    const double getPoint(const double &u) const
    {
        // Assumes that all the piecewise curve is in u[0,1]
        int c = getCurveFromU(u*curves_.size());
        if(c==-1)
            return 0.0;
        return curves_[c]->getPoint(u*curves_.size()-c);
    }
protected:
    const int getCurveFromU(const double& u) const
    {
        if(curves_.size()==0)
            return -1;
        int c = int(u);
        if(c>=curves_.size())
            c = curves_.size()-1;
        return c;
    }
};

} }


#endif
