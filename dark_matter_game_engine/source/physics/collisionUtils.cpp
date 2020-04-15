//*************************************************************************
// DarkMatter OpenGL 3D Game Engine Framework
// Author: Christopher Tall (https://github.com/3dsekai)
// Class Name: -
// Source File: [collisionUtils.cpp]
//
// License:
// Copyright(C) <2020>  <Christopher Tall>
//
// This software is copyrighted.
// The copyright notice and license information in this document must be
// preserved in every copy of the document AS IS. Attribution to the
// original author of this software (see name/website next to "Author:")
// must be given in either the modified source OR in the
// product's documentation.
//
// This software is licensed under the terms of the GNU General Public License
// version 3, as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.If not, see <https://www.gnu.org/licenses/>.
//*************************************************************************

//*************************************************************************
// Includes
//*************************************************************************
#include <math.h>
#include "collisionUtils.h"
//*************************************************************************
// Math Utility Functions
//*************************************************************************
namespace ColDetUtils
{
	//=============================================================================
	// collision detection with line segment and polygon
	// 
	// p0  : position of vertex 0
	// p1  : position of vertex 1
	// p2  : position of vertex 2
	// pos0: current position of colliding object
	// pos1: position of colliding object for next frame 
	//
	// Reference: HAL Notes, Game Programming, 1/14/2015
	//=============================================================================
	bool linePolygonHitCheck(Vec3 p0, Vec3 p1, Vec3 p2, Vec3 pos0, Vec3 pos1)
	{
		bool hit = true;
		Vec3 nor;	//vertex normal
		{// get the facing direction of the polygon
			Vec3 vec1 = p1 - p0;
			Vec3 vec2 = p2 - p1;
			nor = vec1.Cross(vec2);
			nor.Normalize();
			//D3DXVec3Cross( &nor, &vec1, &vec2 );
			//D3DXVec3Normalize( &nor, &nor );
		}

		//get the dot product from point on polygon to colliding obj
		Vec3 vec1 = pos0 - p0; //point 0 to current obj position
		Vec3 vec2 = pos1 - p0; // point 0 to next obj position
		float d1 = nor.Dot(vec1);
		float d2 = nor.Dot(vec2);
		//float d1 = D3DXVec3Dot( &nor, &vec1 );
		//float d2 = D3DXVec3Dot( &nor, &vec2 );

		if( d1 * d2 > 0 )
		{//if d1*d2 is greater than zero, the vectors are pointing in the same direction -
		 //therefore not colliding with polygon
			return 0;
		}

		Vec3 p3;
		{//find the polygon and line segment's intersection point
			d1 = fabs( d1 );	//distance to retrieve internal ratio with current obj position
			d2 = fabs( d2 );	//distance to retrieve internal ration with next obj position
			float a = d1 / ( d1 + d2 );		//internal ratio
			Vec3 vec3 = (vec1 * ( 1 - a )) + (vec2 * a);	//vector from p0 to the intersection point
			p3 = p0 + vec3;		//the intersection point
		}

		pos1 = p3;

		{// check whether or not the intersection point is in the polygon
			//vectors pointing from each vertex to the next
			Vec3 v1 = p1 - p0;
			Vec3 v2 = p2 - p1;
			Vec3 v3 = p0 - p2;

			//the vector from each vertex to the intersection point
			Vec3 v4 = p3 - p1;
			Vec3 v5 = p3 - p2;
			Vec3 v6 = p3 - p0;

			Vec3 n1;
			Vec3 n2;
			Vec3 n3;
			//get cross product of: vector of vertex to vertex and vertex to intersection point
			n1 = v1.Cross(v4);//vec perpendicular to: p0 -> p1 AND p1 -> p3
			n2 = v2.Cross(v5);//vec perpendicular to: p1 -> p2 AND p2 -> p3
			n3 = v3.Cross(v6);//vec perpendicular to: p0 -> p2 AND p0 -> p3
			//D3DXVec3Cross( &n1, &v1, &v4 ); //vec perpendicular to: p0 -> p1 AND p1 -> p3
			//D3DXVec3Cross( &n2, &v2, &v5 ); //vec perpendicular to: p1 -> p2 AND p2 -> p3
			//D3DXVec3Cross( &n3, &v3, &v6 ); //vec perpendicular to: p0 -> p2 AND p0 -> p3

			//normalize the perp vectors
			n1.Normalize();
			n2.Normalize();
			n3.Normalize();
			//D3DXVec3Normalize( &n1, &n1 );
			//D3DXVec3Normalize( &n2, &n2 );
			//D3DXVec3Normalize( &n3, &n3 );

			//subtract the normalized polygon direction with the cross products calculated above.
			Vec3 diff1 = nor - n1;
			Vec3 diff2 = nor - n2;
			Vec3 diff3 = nor - n3;

			//get the length of the difference
			float len1 = diff1.Length();
			float len2 = diff2.Length();
			float len3 = diff3.Length();
			//float len1 = D3DXVec3Length( &diff1 );
			//float len2 = D3DXVec3Length( &diff2 );
			//float len3 = D3DXVec3Length( &diff3 );

			//If the length of the difference is greater than one,
			//it means the two vectors are pointing in opposite directions.
			//If any combination of vectors point in opposite directions the
			//intersection point is not in the polygon (no collision).
			//If they all point in the same direction, there is a collision.
			//For why this is, check 3D math primer for Game Dev p. 66-70 on the cross product.
			//The section that explains why clockwise and counter-clockwise vector rotation
			//results in opposite pointing cross products is the reason.
			if( len1 > 0.1f || len2 > 0.1f || len3 > 0.1f)
			{
				hit = false;
			}
		}
		return hit;
	}
}
