#pragma once

#ifndef DUBINS_H
#define DUBINS_H

#define OUTPUT_FILE_ASTAR_DUBINS "ASTAR_dubinsPath_to_matlab.txt"
#define OUTPUT_FILE_DIJKSTRA_DUBINS "DIJKSTRA_dubinsPath_to_matlab.txt"

// Path types
#define DUBINSCURVES_LSL (0)
#define DUBINSCURVES_LSR (1)
#define DUBINSCURVES_RSL (2)
#define DUBINSCURVES_RSR (3)
#define DUBINSCURVES_RLR (4)
#define DUBINSCURVES_LRL (5)

// Error codes
#define DUBINSCURVES_ERROR_OK        (0)   // No error
#define DUBINSCURVES_ERROR_COCONFIGS (1)   // Colocated configurations
#define DUBINSCURVES_ERROR_PARAM     (2)   // Path parameterisitation error
#define DUBINSCURVES_ERROR_BADRHO    (3)   // the rho value is invalid
#define DUBINSCURVES_ERROR_NOPATH    (4)   // no connection between configurations with this word

using namespace std;

namespace DubinsCurves {

    // The various types of solvers for each of the path types
    typedef int (*DubinsWord)(float, float, float, float*);

    // A complete list of the possible solvers that could give optimal paths 
    extern DubinsWord dubins_words[];

    typedef struct
    {
        float qi[3];       // the initial configuration
        float param[3];    // the lengths of the three segments
        float rho;         // model forward velocity / model angular velocity
        int type;           // path type. one of LSL, LSR, ... 
    } DubinsPath;

    /**
     * Callback function for path sampling
     *
     * @note the q parameter is a configuration
     * @note the t parameter is the distance along the path
     * @note the user_data parameter is forwarded from the caller
     * @note return non-zero to denote sampling should be stopped
     */
    typedef int (*DubinsPathSamplingCallback)(float q[3], float t, void* user_data);

    /**
     * Generate a path from an initial configuration to
     * a target configuration, with a specified maximum turning
     * radii
     *
     * A configuration is (x, y, theta), where theta is in radians, with zero
     * along the line x = 0, and counter-clockwise is positive
     *
     * @param q0    - a configuration specified as an array of x, y, theta
     * @param q1    - a configuration specified as an array of x, y, theta
     * @param rho   - turning radius of the vehicle (forward velocity divided by maximum angular velocity)
     * @param path  - the resultant path
     * @return      - non-zero on error
     */
    int dubins_init(float q0[3], float q1[3], float rho, DubinsPath* path);

    /**
     * Calculate the length of an initialised path
     *
     * @param path - the path to find the length of
     */
    float dubins_path_length(DubinsPath* path);

    /**
     * Extract an integer that represents which path type was used
     *
     * @param path    - an initialised path
     * @return        - one of LSL, LSR, RSL, RSR, RLR or LRL (ie/ 0-5 inclusive)
     */
    int dubins_path_type(DubinsPath* path);

    /**
     * Calculate the configuration along the path, using the parameter t
     *
     * @param path - an initialised path
     * @param t    - a length measure, where 0 <= t < dubins_path_length(path)
     * @param q    - the configuration result
     * @returns    - non-zero if 't' is not in the correct range
     */
    int dubins_path_sample(DubinsPath* path, float t, float q[3]);

    /**
     * Walk along the path at a fixed sampling interval, calling the
     * callback function at each interval
     *
     * @param path      - the path to sample
     * @param cb        - the callback function to call for each sample
     * @param user_data - optional information to pass on to the callback
     * @param stepSize  - the distance along the path for subsequent samples
     */
    int dubins_path_sample_many(DubinsPath* path, DubinsPathSamplingCallback cb, float stepSize, void* user_data);

    /**
     * Convenience function to identify the endpoint of a path
     *
     * @param path - an initialised path
     * @param q    - the configuration result
     */
    int dubins_path_endpoint(DubinsPath* path, float q[3]);

    /**
     * Convenience function to extract a subset of a path
     *
     * @param path    - an initialised path
     * @param t       - a length measure, where 0 < t < dubins_path_length(path)
     * @param newpath - the resultant path
     */
    int dubins_extract_subpath(DubinsPath* path, float t, DubinsPath* newpath);

    // Only exposed for testing purposes
    int dubins_LSL(float alpha, float beta, float d, float* outputs);
    int dubins_RSR(float alpha, float beta, float d, float* outputs);
    int dubins_LSR(float alpha, float beta, float d, float* outputs);
    int dubins_RSL(float alpha, float beta, float d, float* outputs);
    int dubins_LRL(float alpha, float beta, float d, float* outputs);
    int dubins_RLR(float alpha, float beta, float d, float* outputs);


#endif // DUBINS_H

} // namespace DubinsCurves
