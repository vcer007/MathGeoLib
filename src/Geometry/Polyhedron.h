/** @file Polyhedron.h
    @author Jukka Jyl�nki

    This work is copyrighted material and may NOT be used for any kind of commercial or 
    personal advantage and may NOT be copied or redistributed without prior consent
    of the author(s). 

    @brief
*/
#pragma once

#include "Math/MathFwd.h"
#include "Math/float3.h"

//#ifdef MATH_ENABLE_STL_SUPPORT
#include <vector>
//#endif

/// Represents a three-dimensional closed geometric solid defined by flat polygonal faces.
class Polyhedron
{
public:
    struct Face
    {
        /// Specifies the indices of the corner vertices of this polyhedron.
        /// Indices point to the polyhedron vertex array.
        std::vector<int> v;
    };

    /// Specifies the vertices of this polyhedron.
    std::vector<float3> v;

    /// Specifies the individual faces of this polyhedron.
    std::vector<Face> f;

    /// The default ctor creates a null polyhedron (no vertices or faces).
    Polyhedron() {}

    /// Returns the number of vertices in this polyhedron.
    /// The running time of this function is O(1).
    int NumVertices() const { return v.size(); }

    /// Returns the number of faces in this polyhedron.
    /// The running time of this function is O(1).
    int NumFaces() const { return f.size(); }

    /// Returns the number of (unique)edges in this polyhedron.
    /// This function will enumerate through all faces of this polyhedron to compute the number of unique edges.
    /// The running time is linear to the number of faces and vertices in this Polyhedron.
    int NumEdges() const;

    /// Returns the i'th vertex of this polyhedron.
    float3 Vertex(int vertexIndex) const { return v[vertexIndex]; }

    /// Returns the i'th edge of this polyhedron.
    /// Performance warning: Use this function only if you are interested in a single edge of this Polyhedron.
    /// This function calls the Edges() member function to receive a list of all the edges, so it is very slow
    /// if called in a loop, O(n^2).
    LineSegment Edge(int edgeIndex) const;

    /// Returns all the (unique) edges of this polyhedron.
    std::vector<LineSegment> Edges() const;

    /// Returns all the (unique) edges of this polyhedron, as indices to the polyhedron vertex array.
    std::vector<std::pair<int, int> > EdgeIndices() const;

    /// Returns a polygon representing the given face.
    /// The winding order of the polygon will be the same as in the input.
    Polygon FacePolygon(int faceIndex) const;

    /// Returns the plane of the given polygon, treating the positive (visible) direction to be the one where the 
    /// vertices are wound in counter-clockwise order.
    Plane FacePlaneCCW(int faceIndex) const;
    Plane FacePlaneCW(int faceIndex) const;
};
