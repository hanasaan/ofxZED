/*
 * SOFTWARE LICENSE
 * BY USING YOUR CAMERA YOU AGREE TO THIS SOFTWARE LICENSE. BEFORE SETTING IT UP,
 * PLEASE READ THIS SOFTWARE LICENSE CAREFULLY. IF YOU DO NOT ACCEPT THIS
 * SOFTWARE LICENSE, DO NOT USE YOUR CAMERA. RETURN IT TO UNUSED TO STEREOLABS
 * FOR A REFUND. Contact STEREOLABS at support@stereolabs.com
 *
 * 1. Definitions
 *
 * "Authorized Accessory" means a STEREOLABS branded ZED, ZED 2, ZED 2i, ZED Mini, ZED X, ZED X Mini, and a STEREOLABS
 * licensed, third party branded, ZED hardware accessory whose packaging bears the official
 * "Licensed for ZED" logo. The ZED, ZED 2, ZED 2i, ZED Mini, ZED X, ZED X Mini camera are Authorized Accessories
 * solely for purpose of this Software license.
 * "Software" means the Software Development Kit, available on the stereolabs.com website, and including any updates STEREOLABS may make available from
 * time to time.
 * "Unauthorized Accessories" means all hardware accessories other than an Authorized Accessory.
 * "Unauthorized Software" means any software not distributed by STEREOLABS.
 * "You" means the user of a ZED, ZED 2, ZED 2i, ZED Mini, ZED X, ZED X Mini camera.
 *
 * 2. License
 *
 * a. The Software is licensed to You, not sold. You are licensed to use the
 * Software only as downloaded from the stereolabs.com website, and updated by
 * STEREOLABS from time to time. You may not copy or reverse engineer the Software.
 *
 * b. As conditions to this Software license, You agree that:
 *   i. You will use Your Software with ZED, ZED 2, ZED 2i, ZED Mini, ZED X, ZED X Mini camera only and not with any
 *      other device (including). You will not use Unauthorized Accessories. They may
 *      not work or may stop working permanently after a Software update.
 *   ii. You will not use or install any Unauthorized Software with an Authorized Accessory. If You do, Your ZED, ZED 2,
 *      ZED Mini, ZED X camera may stop working permanently at that time or after a later
 *       Software update.
 *   iii. You will not attempt to defeat or circumvent any Software technical limitation,
 *        security, or anti-piracy system. If You do, Your ZED, ZED 2, ZED 2i, ZED Mini, ZED X, ZED X Mini camera may stop
 *        working permanently at that time or after a later Software update.
 *   iv. STEREOLABS may use technical measures, including Software updates, to limit use
 *       of the Software to the ZED, ZED 2, ZED 2i, ZED Mini, ZED X, ZED X Mini camera, to prevent use of Unauthorized
 *       Accessories, and to protect the technical limitations, security and anti-piracy
 *       systems in the ZED, ZED 2, ZED 2i, ZED Mini, ZED X, ZED X Mini camera.
 *   v. STEREOLABS may update the Software from time to time without further notice to You,
 *      for example, to update any technical limitation, security, or anti-piracy system.
 *
 * 3. Warranty
 *
 * The Software is covered by the Limited Warranty for Your ZED, ZED 2, ZED 2i, ZED Mini, ZED X, ZED X Mini camera, and
 * STEREOLABS gives no other guarantee, warranty, or condition for the Software. No one
 * else may give any guarantee, warranty, or condition on STEREOLABS's behalf.
 *
 * 4. EXCLUSION OF CERTAIN DAMAGES
 *
 * STEREOLABS IS NOT RESPONSIBLE FOR ANY INDIRECT, INCIDENTAL, SPECIAL, OR CONSEQUENTIAL
 * DAMAGES; ANY LOSS OF DATA, PRIVACY, CONFIDENTIALITY, OR PROFITS; OR ANY INABILITY TO
 * USE THE SOFTWARE. THESE EXCLUSIONS APPLY EVEN IF STEREOLABS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF THESE DAMAGES, AND EVEN IF ANY REMEDY FAILS OF ITS ESSENTIAL PURPOSE.
 *
 * 5. Choice of Law
 *
 * French law governs the interpretation of this Software license and any claim that
 * STEREOLABS has breached it, regardless of conflict of law principles.
 *
 */

#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>
#include <array>
#include <map>
#include <unordered_set>

#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>


#if defined(_DEBUG) && !defined(ALLOW_BUILD_DEBUG)
#ifdef _MSC_VER
#pragma message("WARNING : 'Debug' builds are not supported since this library was built in 'Release', 'RelWithDebInfo' should be preferred to avoid crashes and memory issues")
#else
#warning("'Debug' builds are not supported since this library was built in 'Release', 'RelWithDebInfo' should be preferred to avoid crashes and memory issues")
#endif
#endif

#define SL_DEPRECATED(str) [[deprecated(str)]]

#if defined _WIN32
#if defined CORE_COMPILATION
#define SL_CORE_EXPORT __declspec(dllexport)
#else
#define SL_CORE_EXPORT
#endif
#elif __GNUC__
#define SL_CORE_EXPORT __attribute__((visibility("default")))
#if defined(__arm__) || defined(__aarch64__)
#define _SL_JETSON_
#endif
#endif

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 
#endif
//#include <Windows.h>
#define __CUSTOM__PRETTY__FUNC__ __FUNCSIG__
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#elif __GNUC__
#include <unistd.h>
#define __CUSTOM__PRETTY__FUNC__ __PRETTY_FUNCTION__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#if defined(__CUDACC__) && defined(__CUDA_ARCH__)
#define _FCT_CPU_GPU_ __host__ __device__ // for CUDA device code
#define IS_FINITE(x) isfinite(x)
#else
#define _FCT_CPU_GPU_
#define IS_FINITE(x) std::isfinite(x)
#endif

namespace sl {

    /**
    \class String
    \ingroup Core_group
    \brief Class defining a string.
     */
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ String {
    public:
        /**
        \brief Default constructor.
        */
        String();
        /**
        \brief Default destructor.
        */
        ~String();

        /**
        \brief Copy constructor.
        */
        String(const String &str);
        /**
        \brief Constructor.
        */
        String(const char *data);

        /**
        \brief Sets the value of the sl::String.
        */
        void set(const char *data);
        /**
        \brief Returns the value of the sl::String.
        */
        const char *get() const;
        /**
        \brief Checks if the sl::String is empty.
        */
        bool empty() const;

        /**
        \brief Copy the value of another sl::String.
        */
        String &operator=(const String &str1);
        /**
        \brief Copy the value of a char*.
        */
        String &operator=(const char *data);

        /**
        \brief Convert the sl::String into a char*.
        */
        operator const char *() {
            return get();
        }

        /**
        \brief Returns the sl::String as a char*.
        */
        const char* c_str() const;

        /**
        \brief Returns the size of the sl::String.
        */
        size_t size();
        /**
        \brief Empties the sl::String.
        */
        void clear();

        /**
        \brief Checks that the value of the current sl::String is equal to the value of another sl::String.
        */
        bool operator==(const String& s) const;

        /**
        \brief Checks that the value of the current sl::String is different to the value of another sl::String.
        */
        bool operator!=(const String& s) const;

    private:
        char *p_data = 0;
        size_t m_size = 0;

        void clean() {
            if (m_size && p_data) free(p_data);
            m_size = 0;
            p_data = 0;
        }
    };

    /**
    \struct Resolution.
    \ingroup Core_group
    \brief Structure containing the width and height of an image.
     */
    struct Resolution {
        /**
        \brief Width of the image in pixels.
        */
        size_t width;
        /**
        \brief Height of the image in pixels.
        */
        size_t height;

        /**
        \brief Default constructor.
        */
        Resolution(size_t w_ = 0, size_t h_ = 0) : width(w_), height(h_) {
        }

        /**
        \brief Returns the area (width * height) of the image.
         */
        size_t area() const {
            return width * height;
        }

        /**
        \brief Tests if the given sl::Resolution has the same properties.
        \return True if the sizes matches.
         */
        bool operator==(const Resolution &that)const {
            return ((width == that.width) && (height == that.height));
        }

        /**
        \brief Tests if the given sl::Resolution has different properties.
        \return True if the sizes are not equal.
         */
        bool operator!=(const Resolution &that)const {
            return ((width != that.width) || (height != that.height));
        }
    };

    /**
    \class Rect.
    \ingroup Core_group
    \brief Class defining a 2D rectangle with top-left corner coordinates and width/height in pixels.
     */
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ Rect {
    public:
        /** 
        \brief x coordinates of top-left corner.
        */
        size_t x;
        /** 
        \brief y coordinates of top-left corner.
        */
        size_t y;
        /** 
        \brief Width of the rectangle in pixels.
        */
        size_t width;
        /** 
        \brief Height of the rectangle in pixels.
        */
        size_t height;

        /**
        \brief Default constructor.
        */
        Rect(size_t x_ = 0, size_t y_ = 0, size_t w_ = 0, size_t h_ = 0) : x(x_), y(y_), width(w_), height(h_) {
        }

        /**
        \brief Returns the area of the rectangle.
         */
        size_t area() {
            return width * height;
        }

        /**
        \brief Tests if the given sl::Rect has the same properties.
        \return True if all the components matches.
         */
        bool operator==(const Rect &that)const {
            return ((x == that.x) && (y == that.y) && (width == that.width) && (height == that.height));
        }

        /**
        \brief Tests if the given sl::Rect has different properties.
        \return True if one of the components does not match.
         */
        bool operator!=(const Rect &that)const {
            return ((x != that.x) || (y != that.y) || (width != that.width) || (height != that.height));
        }

        /**
        \brief Tests if the given sl::Rect is empty (width or/and height is null).
         */
        bool isEmpty() const {
            return (width * height == 0);
        }

        /**
        \brief Tests if this sl::Rect contains the <b>target</b> sl::Rect.
        \return true if this rectangle contains the <b>target</b> rectangle, otherwise false.
        \note This method only returns true if the target rectangle is entirely inside this rectangle (not on the edge).
         */
        inline bool contains(const Rect &target, bool proper = false) const {
            bool ret = false;
            if (!proper)
                ret = (x <= target.x) && (y <= target.y) && (x + width >= target.x + target.width) && (y + height >= target.y + target.height);
            else
                ret = (x < target.x) && (y < target.y) && (x + width > target.x + target.width) && (y + height > target.y + target.height);
            return ret;
        }

        /**
        \brief Tests if this sl::Rect is contained inside the given <b>target</b> sl::Rect.
        \return true if this rectangle is inside the current <b>target</b> sl::Rect, otherwise false.
        \note This method only returns true if this rectangle is entirely inside the <target> rectangle (not on the edge).
         */
        inline bool isContained(const Rect &target, bool proper = false) const {
            bool ret = false;
            if (!proper)
                ret = (x >= target.x) && (y >= target.y) && (x + width <= target.x + target.width) && (y + height <= target.y + target.height);
            else
                ret = (x > target.x) && (y > target.y) && (x + width < target.x + target.width) && (y + height < target.y + target.height);
            return ret;
        }

        /**
        \brief Overloaded method of \ref isContained(). Tests if this sl::Rect is contained inside a given sl::Resolution.
        
        It tests if the current rectangle is contained inside a sl::Rect defined by Rect(0, 0, resolution.width, resolution.height).
        \return true if this rectangle is inside the rectangle defined by Rect(0, 0, resolution.width, resolution.height), otherwise false.
        \note This method only returns true if this rectangle is entirely inside the rectangle defined by the resolution (not on the edge).
         */
        inline bool isContained(const Resolution &resolution, bool proper = false) const {
            bool ret = false;
            if (!proper)
                ret = (x + width <= resolution.width) && (y + height <= resolution.height);
            else
                ret = x > 0 && y > 0 && (x + width < resolution.width) && (y + height < resolution.height);
            return ret;
        }

    };

    /**
    \enum UNIT
    \ingroup Core_group
    \brief Lists available units for measures.
     */
    enum class UNIT {
        MILLIMETER, /**< International System (1/1000 meters) */
        CENTIMETER, /**< International System (1/100 meters) */
        METER, /**< International System (1 meter)*/
        INCH, /**< Imperial Unit (1/12 feet) */
        FOOT, /**< Imperial Unit (1 foot)*/
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const UNIT &unit);

    inline std::ostream &operator<<(std::ostream &os, const UNIT &unit) {
        return os << toString(unit);
    }
    ///@endcond

    /**
    \enum COORDINATE_SYSTEM
    \ingroup Core_group
    \brief Lists available coordinates systems for positional tracking and 3D measures.

    \image html CoordinateSystem.webp
     */
    enum class COORDINATE_SYSTEM {
        IMAGE, /**< Standard coordinates system in computer vision.\n Used in OpenCV: see <a href="http://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html">here</a>. */
        LEFT_HANDED_Y_UP, /**< Left-handed with Y up and Z forward.\n Used in Unity with DirectX. */
        RIGHT_HANDED_Y_UP, /**< Right-handed with Y pointing up and Z backward.\n Used in OpenGL. */
        RIGHT_HANDED_Z_UP, /**< Right-handed with Z pointing up and Y forward.\n Used in 3DSMax. */
        LEFT_HANDED_Z_UP, /**< Left-handed with Z axis pointing up and X forward.\n Used in Unreal Engine. */
        RIGHT_HANDED_Z_UP_X_FWD, /**< Right-handed with Z pointing up and X forward.\n Used in ROS (REP 103). */
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const COORDINATE_SYSTEM &coord_system);

    inline std::ostream &operator<<(std::ostream &os, const COORDINATE_SYSTEM &coord_system) {
        return os << toString(coord_system);
    }
    ///@endcond

    /**
    \enum ERROR_CODE
    \ingroup Core_group
    \brief Lists error codes in the ZED SDK.
     */
    enum class ERROR_CODE {
        SENSORS_DATA_REQUIRED = -3, /**< The input data does not contains the high frequency sensors data, this is usually because it requires newer SVO/Streaming. In order to work this modules needs inertial data present in it input.*/
        CORRUPTED_FRAME = -2, /**< The image could be corrupted (enabled with the parameter InitParameters::enable_image_validity_check).*/
        CAMERA_REBOOTING = -1, /**< The camera is currently rebooting.*/
        SUCCESS = 0, /**< Standard code for successful behavior.*/
        FAILURE = 1, /**< Standard code for unsuccessful behavior.*/
        NO_GPU_COMPATIBLE = 2, /**< No GPU found or CUDA capability of the device is not supported.*/
        NOT_ENOUGH_GPU_MEMORY = 3, /**< Not enough GPU memory for this depth mode, try a different mode (such as \ref DEPTH_MODE "PERFORMANCE"), or increase the minimum depth value (see InitParameters::depth_minimum_distance).*/
        CAMERA_NOT_DETECTED = 4, /**< No camera was detected.*/
        SENSORS_NOT_INITIALIZED = 5, /**< The MCU that controls the sensors module has an invalid serial number. You can try to recover it by launching the <b>ZED Diagnostic</b> tool from the command line with the option <code>-r</code>.*/
        SENSORS_NOT_AVAILABLE = 6, /**< A camera with sensor is detected but the sensors (IMU, barometer, ...) cannot be opened. Only the \ref MODEL "MODEL::ZED" does not has sensors. Unplug/replug is required.*/
        INVALID_RESOLUTION = 7, /**< In case of invalid resolution parameter, such as an upsize beyond the original image size in Camera::retrieveImage. */
        LOW_USB_BANDWIDTH = 8, /**< Insufficient bandwidth for the correct use of the camera. This issue can occur when you use multiple cameras or a USB 2.0 port.*/
        CALIBRATION_FILE_NOT_AVAILABLE = 9, /**< The calibration file of the camera is not found on the host machine. Use <b>ZED Explorer</b> or <b>ZED Calibration</b> to download the factory calibration file.*/
        INVALID_CALIBRATION_FILE = 10, /**< The calibration file is not valid. Try to download the factory calibration file or recalibrate your camera using <b>ZED Calibration</b>.*/
        INVALID_SVO_FILE = 11, /**< The provided SVO file is not valid.*/
        SVO_RECORDING_ERROR = 12, /**< An error occurred while trying to record an SVO (not enough free storage, invalid file, ...).*/
        SVO_UNSUPPORTED_COMPRESSION = 13, /**< An SVO related error, occurs when NVIDIA based compression cannot be loaded.*/
        END_OF_SVOFILE_REACHED = 14, /**< SVO end of file has been reached.\n No frame will be available until the SVO position is reset.*/
        INVALID_COORDINATE_SYSTEM = 15, /**< The requested coordinate system is not available.*/
        INVALID_FIRMWARE = 16, /**< The firmware of the camera is out of date. Update to the latest version.*/
        INVALID_FUNCTION_PARAMETERS = 17, /**< Invalid parameters have been given for the function. */
        CUDA_ERROR = 18, /**< A CUDA error has been detected in the process, in Camera.grab() or Camera.retrieveXXX() only. Activate verbose in Camera.open() for more info.*/
        CAMERA_NOT_INITIALIZED = 19, /**< The ZED SDK is not initialized. Probably a missing call to Camera.open().*/
        NVIDIA_DRIVER_OUT_OF_DATE = 20, /**< Your NVIDIA driver is too old and not compatible with your current CUDA version. */
        INVALID_FUNCTION_CALL = 21, /**< The call of the function is not valid in the current context. Could be a missing call of Camera.open(). */
        CORRUPTED_SDK_INSTALLATION = 22, /**< The ZED SDK was not able to load its dependencies or some assets are missing. Reinstall the ZED SDK or check for missing dependencies (cuDNN, TensorRT). */
        INCOMPATIBLE_SDK_VERSION = 23, /**< The installed ZED SDK is incompatible with the one used to compile the program. */
        INVALID_AREA_FILE = 24, /**< The given area file does not exist. Check the path. */
        INCOMPATIBLE_AREA_FILE = 25, /**< The area file does not contain enough data to be used or the \ref DEPTH_MODE used during the creation of the area file is different from the one currently set. */
        CAMERA_FAILED_TO_SETUP = 26, /**< Failed to open the camera at the proper resolution. Try another resolution or make sure that the UVC driver is properly installed.*/
        CAMERA_DETECTION_ISSUE = 27, /**< Your camera can not be opened. Try replugging it to another port or flipping the USB-C connector (if there is one).*/
        CANNOT_START_CAMERA_STREAM = 28, /**< Cannot start the camera stream. Make sure your camera is not already used by another process or blocked by firewall or antivirus.*/
        NO_GPU_DETECTED = 29, /**< No GPU found. CUDA is unable to list it. Can be a driver/reboot issue.*/
        PLANE_NOT_FOUND = 30, /**< Plane not found. Either no plane is detected in the scene, at the location or corresponding to the floor, or the floor plane doesn't match the prior given.*/
        MODULE_NOT_COMPATIBLE_WITH_CAMERA = 31, /**< The module you try to use is not compatible with your camera \ref MODEL. \note \ref MODEL "MODEL::ZED" does not has an IMU and does not support the AI modules.*/
        MOTION_SENSORS_REQUIRED = 32, /**< The module needs the sensors to be enabled (see InitParameters::sensors_required). */
        MODULE_NOT_COMPATIBLE_WITH_CUDA_VERSION = 33, /**< The module needs a newer version of CUDA. */
        ///@cond SHOWHIDDEN 
        LAST = 35
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const ERROR_CODE &errorCode);
    ///@endcond

    /**
    \ingroup Core_group
    \brief Provide a concise sl::ERROR_CODE string.
    \return A concise sl::ERROR_CODE string for the user.
     */
    String /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ toVerbose(const ERROR_CODE &errorCode);


    ///@cond SHOWHIDDEN

    inline std::ostream &operator<<(std::ostream &os, const ERROR_CODE &errorCode) {
        return os << toString(errorCode);
    }
    ///@endcond

    /**
    \enum MODEL
    \ingroup Video_group
    \brief Lists ZED camera model.
     */
    enum class MODEL {
        ZED, /**< ZED camera model */
        ZED_M, /**< ZED Mini (ZED M) camera model */
        ZED2, /**< ZED 2 camera model */
        ZED2i, /**< ZED 2i camera model */
        ZED_X, /**< ZED X camera model */
        ZED_XM, /**< ZED X Mini (ZED XM) camera model */
        VIRTUAL_ZED_X =11, /**< Virtual ZED-X generated from 2 ZED-XOne */
        ZED_XONE_GS =30, /**< ZED XOne with global shutter AR0234 sensor */
        ZED_XONE_UHD =31, /**< ZED XOne with 4K rolling shutter IMX678 sensor */
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const MODEL &model);

    inline std::ostream &operator<<(std::ostream &os, const MODEL &model) {
        return os << toString(model);
    }
    ///@endcond

    /**
    \enum INPUT_TYPE
    \ingroup Video_group
    \brief Lists available input types in the ZED SDK.
     */
    enum class INPUT_TYPE {
        USB, /**< USB input mode */
        SVO, /**<  SVO file input mode */
        STREAM, /**< STREAM input mode (requires to use \ref Camera.enableStreaming "enableStreaming()" / \ref Camera.disableStreaming "disableStreaming()"" on the "sender" side) */
        GMSL, /**< GMSL input mode (only on NVIDIA Jetson) */
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const INPUT_TYPE &input_type);

    inline std::ostream &operator<<(std::ostream &os, const INPUT_TYPE &input_type) {
        return os << toString(input_type);
    }
    ///@endcond

    /**
    \enum CAMERA_STATE
    \ingroup Video_group
    \brief Lists possible camera states.
     */
    enum class CAMERA_STATE {
        AVAILABLE, /**< The camera can be opened by the ZED SDK. */
        NOT_AVAILABLE, /**< The camera is already opened and unavailable. */
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const CAMERA_STATE &camera_state);

    inline std::ostream &operator<<(std::ostream &os, const CAMERA_STATE &camera_state) {
        return os << toString(camera_state);
    }
    ///@endcond

    /**
    \ingroup Video_group
    \brief Structure containing information about the properties of a camera.

    \note A \ref camera_model \ref MODEL "sl::MODEL::ZED_M" with an id '-1' can be due to an inverted USB-C cable.
     */
    struct DeviceProperties {
        /**
        \brief State of the camera.

        Default: \ref CAMERA_STATE "sl::CAMERA_STATE::NOT_AVAILABLE"
         */
        sl::CAMERA_STATE camera_state = sl::CAMERA_STATE::NOT_AVAILABLE;

        /**
        \brief Id of the camera.

        Default: -1
         */
        int id = -1;

        /**
        \brief System path of the camera.
         */
        sl::String path;

        /**
        \brief Model of the camera.
         */
        sl::MODEL camera_model = sl::MODEL::LAST;

        /**
        \brief Serial number of the camera.

        Default: 0 
        \warning Not provided for Windows.
         */
        unsigned int serial_number = 0;

        /**
        \brief Input type of the camera.
         */
        INPUT_TYPE input_type;
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const DeviceProperties &properties);

    inline std::ostream &operator<<(std::ostream &os, const DeviceProperties &properties) {
        return os << toString(properties);
    }
    ///@endcond

    /**
    \enum STREAMING_CODEC
    \ingroup Video_group
    \brief Lists the different encoding types for image streaming.
     */
    enum class STREAMING_CODEC {
        H264, /**< AVCHD/H264 encoding*/
        H265, /**< HEVC/H265 encoding*/
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    /**
    \ingroup Video_group
    \brief Structure containing information about the properties of a streaming device. 
     */
    struct StreamingProperties {
        /**
        \brief IP address of the streaming device.

        Default: ""
         */
        sl::String ip = "";

        /**
        \brief Streaming port of the streaming device.

        Default: 0
         */
        unsigned short port = 0;

        /**
        \brief Serial number of the streaming camera.

        Default: 0
         */
        unsigned int serial_number = 0;

        /**
        \brief Current bitrate of encoding of the streaming device.

        Default: 0
         */
        int current_bitrate = 0;

        /**
        \brief Current codec used for compression in streaming device.

        Default: \ref STREAMING_CODEC "sl::STREAMING_CODEC::H265"
         */
        STREAMING_CODEC codec = STREAMING_CODEC::H265;
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const StreamingProperties &properties);

    inline std::ostream &operator<<(std::ostream &os, const StreamingProperties &properties) {
        return os << toString(properties);
    }
    ///@endcond

    /**
    \enum SENSOR_TYPE
    \ingroup Sensors_group
    \brief Lists available sensor types.
    \note Sensors are not available on \ref MODEL "sl::MODEL::ZED".
     */
    enum class SENSOR_TYPE {
        ACCELEROMETER, /**< Three-axis accelerometer sensor to measure the inertial accelerations. */
        GYROSCOPE, /**< Three-axis gyroscope sensor to measure the angular velocities. */
        MAGNETOMETER, /**< Three-axis magnetometer sensor to measure the orientation of the device with respect to the Earth's magnetic field. */
        BAROMETER, /**< Barometer sensor to measure the atmospheric pressure. */
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const SENSOR_TYPE &sens);

    inline std::ostream &operator<<(std::ostream &os, const SENSOR_TYPE &sens) {
        return os << toString(sens);
    }
    ///@endcond

    /**
    \enum SENSORS_UNIT
    \ingroup Sensors_group
    \brief Lists available measurement units of onboard sensors.
    \note Sensors are not available on \ref MODEL "sl::MODEL::ZED".
     */
    enum class SENSORS_UNIT {
        M_SEC_2, /**< m/s² (acceleration) */
        DEG_SEC, /**< deg/s (angular velocity) */
        U_T, /**< μT (magnetic field) */
        HPA, /**< hPa (atmospheric pressure) */
        CELSIUS, /**< °C (temperature) */
        HERTZ, /**< Hz (frequency) */
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const SENSORS_UNIT &unit);

    inline std::ostream &operator<<(std::ostream &os, const SENSORS_UNIT &unit) {
        return os << toString(unit);
    }
    ///@endcond

    /**
    \enum BUS_TYPE
    \ingroup Video_group
    \brief Lists available LIVE input type in the ZED SDK.
     */
    enum class BUS_TYPE {
        USB, /**< USB input mode */
        GMSL, /**< GMSL input mode \note Only on NVIDIA Jetson. */
        AUTO, /**< Automatically select the input type.\n Trying first for available USB cameras, then GMSL. */
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const BUS_TYPE &bus_type);

    inline std::ostream &operator<<(std::ostream &os, const BUS_TYPE &bus_type) {
        return os << toString(bus_type);
    }
    ///@endcond

    /**
    \class InputType
    \ingroup Video_group
    \brief Class defining the input type used in the ZED SDK.
    
    It can be used to select a specific camera with an id or serial number, or from a SVO file.
     */
    class SL_CORE_EXPORT InputType {
        friend class Camera;
        friend struct InitParameters;
    public:

        /**
        \brief Lists input types in the ZED SDK.
        */
        enum class INPUT_TYPE {
            USB_ID, /**< USB input from an id*/
            USB_SERIAL, /**< USB input from a serial number*/
            SVO_FILE, /**< SVO file input*/
            STREAM, /**< STREAM input (requires to use \ref Camera.enableStreaming "enableStreaming()" / \ref Camera.disableStreaming "disableStreaming()"" on the "sender" side) */
            GMSL_ID, /**< GMSL input from an id (only on NVIDIA Jetson) */
            GMSL_SERIAL, /**< GMSL input from a serial number (only on NVIDIA Jetson) */
            ///@cond SHOWHIDDEN
            LAST
            ///@endcond
        };

        /**
        \brief Default constructor.
         */
        InputType();

        /**
        \brief Copy constructor.
         */
        InputType(const InputType &type);

        /**
        \brief Set the input as the camera with specified id (for USB or GMSL cameras only).
        \param id : Id of the camera to open.
        \param bus_type : Whether the camera is a USB or a GMSL camera.
         */
        void setFromCameraID(int id = -1, sl::BUS_TYPE bus_type = sl::BUS_TYPE::AUTO);

        /**
        \brief Set the input as the camera with specified serial number (for USB or GMSL cameras).
        \param camera_serial_number : Serial number of the camera to open.
        \param bus_type : Whether the camera is a USB or a GMSL camera.
         */
        void setFromSerialNumber(unsigned int camera_serial_number, sl::BUS_TYPE bus_type = sl::BUS_TYPE::AUTO);

        /**
        \brief Set the input as the SVO specified with the filename.
        \param svo_input_filename : Path of the SVO file to open.
         */
        void setFromSVOFile(sl::String svo_input_filename);

        /**
        \brief Set the input as the stream defined by the IP address and the port of the sending device.
        \param sender_ip : IP address of the streaming sender.
        \param port : Port on which to listen. Default: 30000
        \note The protocol used for the streaming module is based on RTP/RTCP.
        \warning Port must be even number, since the port+1 is used for control data.
         */
        void setFromStream(sl::String senderIP, unsigned short port = 30000);

        /**
        \brief Returns the current input type.
         */
        INPUT_TYPE getType() {
            return type;
        }

        /**
        \brief Returns the current input configuration as a string e.g: SVO name, serial number, streaming ip, etc.
         */
        sl::String getConfiguration() {
            return configuration;
        }

        /**
        \brief Check whether the input is set.
         */
        bool isInit() {
            return init_;
        }

    private:
        INPUT_TYPE type = INPUT_TYPE::LAST;
        sl::String configuration = "0";
        bool init_ = false;
    };

    /**
    \enum OBJECT_DETECTION_MODEL
    \ingroup Object_group
    \brief Lists available models for the object detection module.
     */
    enum class OBJECT_DETECTION_MODEL {
        MULTI_CLASS_BOX_FAST, /**< Any objects, bounding box based. */
        MULTI_CLASS_BOX_MEDIUM, /**< Any objects, bounding box based, compromise between accuracy and speed. */
        MULTI_CLASS_BOX_ACCURATE, /**< Any objects, bounding box based, more accurate but slower than the base model. */
        PERSON_HEAD_BOX_FAST, /**< Bounding box detector specialized in person heads particularly well suited for crowded environments. The person localization is also improved. */
        PERSON_HEAD_BOX_ACCURATE, /**< Bounding box detector specialized in person heads, particularly well suited for crowded environments. The person localization is also improved, more accurate but slower than the base model.*/
        CUSTOM_BOX_OBJECTS, /**< For external inference, using your own custom model and/or frameworks. This mode disables the internal inference engine, the 2D bounding box detection must be provided. */
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const OBJECT_DETECTION_MODEL& input_type);

    inline std::ostream& operator<<(std::ostream& os, const OBJECT_DETECTION_MODEL& input_type) {
        return os << toString(input_type);
    }
    ///@endcond

    /**
    \enum BODY_TRACKING_MODEL
    \ingroup Body_group
    \brief Lists available models for the body tracking module.
     */
    enum class BODY_TRACKING_MODEL {
        HUMAN_BODY_FAST, /**< Keypoints based, specific to human skeleton, real time performance even on Jetson or low end GPU cards. */
        HUMAN_BODY_MEDIUM, /**< Keypoints based, specific to human skeleton, compromise between accuracy and speed. */
        HUMAN_BODY_ACCURATE, /**< Keypoints based, specific to human skeleton, state of the art accuracy, requires powerful GPU. */
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const BODY_TRACKING_MODEL& input_type);

    inline std::ostream& operator<<(std::ostream& os, const BODY_TRACKING_MODEL& input_type) {
        return os << toString(input_type);
    }
    ///@endcond

    ///@cond SHOWHIDDEN
    UNIT /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ str2unit(String unit);
    ///@endcond

    /**
    \enum AI_MODELS
    \ingroup Object_group
    \brief Lists available AI models.
     */
    enum class AI_MODELS {
        MULTI_CLASS_DETECTION, /**< Related to [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_FAST](\ref OBJECT_DETECTION_MODEL)*/
        MULTI_CLASS_MEDIUM_DETECTION, /**< Related to [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_MEDIUM](\ref OBJECT_DETECTION_MODEL)*/
        MULTI_CLASS_ACCURATE_DETECTION, /**< Related to [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_ACCURATE](\ref OBJECT_DETECTION_MODEL)*/
        HUMAN_BODY_FAST_DETECTION, /**< Related to [sl::BODY_TRACKING_MODEL::HUMAN_BODY_FAST](\ref BODY_TRACKING_MODEL)*/
        HUMAN_BODY_MEDIUM_DETECTION, /**< Related to [sl::BODY_TRACKING_MODEL::HUMAN_BODY_MEDIUM](\ref BODY_TRACKING_MODEL)*/
        HUMAN_BODY_ACCURATE_DETECTION, /**< Related to [sl::BODY_TRACKING_MODEL::HUMAN_BODY_ACCURATE](\ref BODY_TRACKING_MODEL)*/
        HUMAN_BODY_38_FAST_DETECTION, /**< Related to [sl::BODY_TRACKING_MODEL::HUMAN_BODY_FAST](\ref BODY_TRACKING_MODEL)*/
        HUMAN_BODY_38_MEDIUM_DETECTION, /**< Related to [sl::BODY_TRACKING_MODEL::HUMAN_BODY_FAST](\ref BODY_TRACKING_MODEL)*/
        HUMAN_BODY_38_ACCURATE_DETECTION, /**< Related to [sl::BODY_TRACKING_MODEL::HUMAN_BODY_FAST](\ref BODY_TRACKING_MODEL)*/
        PERSON_HEAD_DETECTION, /**< Related to [sl::OBJECT_DETECTION_MODEL::PERSON_HEAD_BOX_FAST](\ref OBJECT_DETECTION_MODEL)*/
        PERSON_HEAD_ACCURATE_DETECTION, /**< Related to [sl::OBJECT_DETECTION_MODEL::PERSON_HEAD_BOX_ACCURATE](\ref OBJECT_DETECTION_MODEL)*/
        REID_ASSOCIATION, /**< Related to sl::BatchParameters.enable*/
        NEURAL_DEPTH, /**< Related to [sl::DEPTH_MODE::NEURAL](\ref DEPTH_MODE)*/
        NEURAL_PLUS_DEPTH, /**< Related to [sl::DEPTH_MODE::NEURAL_PLUS](\ref DEPTH_MODE)*/
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ toString(const AI_MODELS &model);

    inline ::std::ostream &operator<<(::std::ostream &os, const AI_MODELS &model) {
        return os << toString(model);
    }
    ///@endcond

    /**
    \class AI_Model_status
    \ingroup Object_group
    \brief Structure containing AI model status.
     */
    struct AI_Model_status {
        bool downloaded; /**< \brief The model file is currently present on the host.*/
        bool optimized; /**< \brief An engine file with the expected architecture is found.*/
    };

    /*!
    \ingroup Core_group
    \brief Blocks the execution of the current thread for \b time milliseconds.
    \param time : Number of milliseconds to wait.
     */
    inline void sleep_ms(int time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }

    /*!
    \ingroup Core_group
    \brief Blocks the execution of the current thread for \b time microseconds.
    \param time : Number of microseconds to wait.
     */
    inline void sleep_us(int time) {
        std::this_thread::sleep_for(std::chrono::microseconds(time));
    }


    /// @cond
    template <typename T>
    class Vector3;
    template <typename T>
    class Vector4;
    ///@endcond

    /**
    \class Matrix3f
    \ingroup Core_group
    \brief Class representing a generic 3*3 matrix.

    It is defined in a row-major order, it means that, in the value buffer, the entire first row is stored first, followed by the entire second row, and so on.
    \n The data value of the matrix can be accessed with the 'r' ptr or by element attribute.
    |     |     |     |
    |-----|-----|-----|
    | r00 | r01 | r02 |
    | r10 | r11 | r12 |
    | r20 | r21 | r22 | 
     */
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ Matrix3f {
    public:
        /// @cond
        static const int nbElem = 9;

        union {
            // access inner data by dedicated ref.

            struct {
                float r00, r01, r02, r10, r11, r12, r20, r21, r22;
            };
            // ptr to inner data
            float r[nbElem];
        };
        /// @endcond

        /**
        \brief Default constructor.
         */
        Matrix3f();

        /**
        \brief Copy constructor (deep copy).
         */
        Matrix3f(float data[]);

        /**
        \brief Cpy constructor (deep copy).
        \param mat : sl::Matrix3f to copy.
         */
        Matrix3f(const Matrix3f &mat);

        /**
        \brief Gives the result of the multiplication between two sl::Matrix3f.
         */
        Matrix3f operator*(const Matrix3f &mat) const;

        /**
        \brief Gives the result of the multiplication between a sl::Matrix3f and a scalar.
         */
        Matrix3f operator*(const float &scalar) const;

        /**
        \brief Gives the result of the addition between two sl::Matrix3f.
         */
        Matrix3f operator+(const Matrix3f &mat) const;

        /**
        \brief Gives the result of the addition between a sl::Matrix3f and a scalar.
         */
        Matrix3f operator+(const float &scalar) const;

        /**
        \brief Gives the result of the subtraction between two sl::Matrix3f.
         */
        Matrix3f operator-(const Matrix3f &mat) const;

        /**
        \brief Gives the result of the subtraction between a sl::Matrix3f and a scalar.
         */
        Matrix3f operator-(const float &scalar) const;

        /**
        \brief Test two sl::Matrix3f equality.
         */
        bool operator==(const Matrix3f &mat) const;

        /**
        \brief Test two sl::Matrix3f inequality.
         */
        bool operator!=(const Matrix3f &mat) const;

        /**
        \brief Gets access to a specific point in the sl::Matrix3f (read/write).
        \param u : Row to get the value from.
        \param v : Column to get the value from.
        \return The value at the u, v coordinates.
         */
        float &operator()(int u, int v);

        /**
        \brief Sets the sl::Matrix3f to its inverse.
         */
        void inverse();

        /**
        \brief Returns the inverse of a sl::Matrix3f.
        \param rotation : sl::Matrix3f to compute the inverse from.
        \return The inverse of the sl::Matrix3f given as input.
         */
        static Matrix3f inverse(const Matrix3f &rotation);

        /**
        \brief Sets the sl::Matrix3f to its transpose.
         */
        void transpose();

        /**
        \brief Returns the transpose of a sl::Matrix3f.
        \param rotation : sl::Matrix3f to compute the transpose from.
        \return The transpose of the sl::Matrix3f given as input.
         */
        static Matrix3f transpose(const Matrix3f &rotation);

        /**
        \brief Sets the sl::Matrix3f to identity.
         */
        void setIdentity();

        /**
        \brief Creates an identity sl::Matrix3f.
        \return A sl::Matrix3f set to identity.
         */
        static Matrix3f identity();

        /**
        \brief Sets the sl::Matrix3f to zero.
         */
        void setZeros();

        /**
        \brief Creates a sl::Matrix3f filled with zeros.
        \return A sl::Matrix3f filled with zeros.
         */
        static Matrix3f zeros();

        /**
        \brief Returns the components of the sl::Matrix3f in a sl::String.
        \return A sl::String containing the components of the current sl::Matrix3f.
         */
        String getInfos();

        /**
        \brief Name of the matrix (optional).
         */
        String matrix_name;
    };

    /**
    \class Matrix4f
    \ingroup Core_group
    \brief Class representing a generic 4*4 matrix.

    It is defined in a row-major order, it means that, in the value buffer, the entire first row is stored first, followed by the entire second row, and so on.
    \n The data value of the matrix can be accessed with the 'm' ptr or by element attribute.
    | | | | |
    |-|-|-|-|
    | r00 | r01 | r02 | tx |
    | r10 | r11 | r12 | ty |
    | r20 | r21 | r22 | tz |
    | m30 | m31 | m32 | m33 |
     */
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ Matrix4f {
    public:
        /// @cond
        static const int nbElem = 16;

        union {

            struct {
                float r00, r01, r02, tx, r10, r11, r12, ty, r20, r21, r22, tz, m30, m31, m32, m33;
            };
            // ptr to inner data.
            float m[nbElem];
        };
        /// @endcond

        /**
        \brief Default constructor.
         */
        Matrix4f();

        /**
        \brief Copy constructor (deep copy).
         */
        Matrix4f(float data[]);

        /**
        \brief Copy constructor (deep copy).
        \param mat : sl::Matrix3f to copy.
         */
        Matrix4f(const Matrix4f &mat);

        /**
        \brief Gives the result of the multiplication between two sl::Matrix4f.
         */
        Matrix4f operator*(const Matrix4f &mat) const;

        /**
        \brief Gives the result of the multiplication between a sl::Matrix4f and a sl::float4.
         */
        Matrix4f operator*(const Vector4<float> &vect) const;

        /**
        \brief Gives the result of the multiplication between a sl::Matrix4f and a scalar.
         */
        Matrix4f operator*(const float &scalar) const;

        /**
        \brief Gives the result of the addition between two sl::Matrix4f.
         */
        Matrix4f operator+(const Matrix4f &mat) const;

        /**
        \brief Gives the result of the addition between a sl::Matrix4f and a scalar.
         */
        Matrix4f operator+(const float &scalar) const;

        /**
        \brief Gives the result of the subtraction between two sl::Matrix4f.
         */
        Matrix4f operator-(const Matrix4f &mat) const;

        /**
        \brief Gives the result of the subtraction between a sl::Matrix4f and a scalar.
         */
        Matrix4f operator-(const float &scalar) const;

        /**
        \brief Tests two sl::Matrix4f equality.
         */
        bool operator==(const Matrix4f &mat) const;

        /**
        \brief Tests two sl::Matrix4f inequality.
         */
        bool operator!=(const Matrix4f &mat) const;

        /**
        \brief Gets access to a specific point in the sl::Matrix4f (read/write).
        \param u : Row to get the value from.
        \param v : Column to get the value from.
        \return The value at the u, v coordinates.
         */
        float &operator()(int u, int v);

        /**
        \brief Sets the sl::Matrix4f to its inverse.
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if the inverse has been computed, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) is not (det = 0).
         */
        ERROR_CODE inverse();

        /**
        \brief Creates the inverse of a sl::Matrix4f.
        \param mat : sl::Matrix4f to compute the inverse from.
        \return The inverse of the sl::Matrix4f given as input.
         */
        static Matrix4f inverse(const Matrix4f &mat);

        /**
        \brief Sets the sl::Matrix4f to its transpose.
         */
        void transpose();

        /**
        \brief Creates the transpose of a sl::Matrix4f.
        \param mat : sl::Matrix4f to compute the transpose from.
        \return The transpose of the sl::Matrix4f given as input.
         */
        static Matrix4f transpose(const Matrix4f &mat);

        /**
        \brief Sets the sl::Matrix4f to identity.
         */
        void setIdentity();

        /**
        \brief Creates an identity sl::Matrix4f.
        \return A sl::Matrix4f set to identity.
         */
        static Matrix4f identity();

        /**
        \brief Sets the sl::Matrix4f to zero.
         */
        void setZeros();

        /**
        \brief Creates a sl::Matrix4f filled with zeros.
        \return A sl::Matrix4f filled with zero.
         */
        static Matrix4f zeros();

        /**
        \brief Sets a sl::Matrix3f inside the sl::Matrix4f.
        \note Can be used to set the rotation matrix when the sl::Matrix4f is a pose or an isometric matrix.
        \param input  : Sub-matrix to put inside the sl::Matrix4f.
        \param row : Index of the row to start the 3x3 block. Must be 0 or 1.
        \param column : Index of the column to start the 3x3 block. Must be 0 or 1.
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.
         */
        ERROR_CODE setSubMatrix3f(Matrix3f input, int row = 0, int column = 0);

        /**
        \brief Sets a sl::Vector3 inside the sl::Matrix4f at the specified column index.
        \note Can be used to set the translation/position matrix when the sl::Matrix4f is a pose or an isometry.
        \param input  : Sub-vector to put inside the sl::Matrix4f.
        \param column : Index of the column to start the 3x3 block. By default, it is the last column (translation for a sl::Pose).
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.
         */
        ERROR_CODE setSubVector3f(Vector3<float> input, int column = 3);

        /**
        \brief Sets a sl::Vector4 inside the sl::Matrix4f at the specified column index.
        \note Can be used to set the translation/position matrix when the sl::Matrix4f is a pose or an isometry.
        \param input  : Sub-vector to put inside the sl::Matrix4f.
        \param column : Index of the column to start the 3x3 block. By default, it is the last column (translation for a sl::Pose).
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.
         */
        ERROR_CODE setSubVector4f(Vector4<float> input, int column = 3);

        /**
        \brief Returns the components of the sl::Matrix4f in a sl::String.
        \return A sl::String containing the components of the current sl::Matrix4f.
         */
        String getInfos();

        /**
        \brief Name of the matrix (optional).
         */
        String matrix_name;
    };

    /**
    \class Vector2
    \ingroup Core_group
    \brief Class representing a 2-dimensional vector for both CPU and GPU.
     */
    template <typename T>
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ Vector2 {
        static const int nbElem = 2;
    public:
        /// @cond

        union {

            struct {
                T x, y;
            };
            T v[nbElem];
        };
        /// @endcond

        /**
        \brief Return the size of the sl::Vector2.
        \return 2
        */
        inline _FCT_CPU_GPU_ int size() const {
            return nbElem;
        }

        /**
        \brief Default constructor.

        Initialize the sl::Vector2 to 0.
        */
        _FCT_CPU_GPU_ Vector2() : x(0), y(0) {
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector2 to ( \b t, \b t ).
        */
        _FCT_CPU_GPU_ Vector2(const T &t) {
            this->x = t;
            this->y = t;
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector2 with the component of the argument.
        */
        _FCT_CPU_GPU_ Vector2(const T *tp) {
            this->x = tp[0];
            this->y = tp[1];
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector2 to ( \b v0, \b v1 ).
        */
        _FCT_CPU_GPU_ Vector2(const T v0, const T v1) {
            this->x = v0;
            this->y = v1;
        }

        /**
        \brief Copy constructor.

        Initialize the sl::Vector2 by copying another sl::Vector2.
        */
        _FCT_CPU_GPU_ Vector2<T>(const Vector2<T> &v) {
            this->x = v.x;
            this->y = v.y;
        }

        /**
        \brief Returns a pointer of the first component.
        */
        _FCT_CPU_GPU_ const T *ptr() const {
            return &this->v[0];
        }

        /**
        \brief Sets the components of the sl::Vector2 to the values of the argument.
        */
        inline _FCT_CPU_GPU_ Vector2 &setValues(const T *b) {
            this->x = b[0];
            this->y = b[1];
            return *this;
        }

        /**
        \brief Returns the \b i-th component.
        */
        _FCT_CPU_GPU_ T &operator[](int i) {
            return this->v[i];
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> &operator*=(Vector2<T>&itself, T d) {
            itself.x *= d;
            itself.y *= d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> &operator*=(Vector2<T>&itself, const Vector2<T> &b) {
            itself.x *= b.x;
            itself.y *= b.y;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> &operator/=(Vector2<T>&itself, T d) {
            if (d == 0) return itself;
            itself.x /= d;
            itself.y /= d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> &operator/=(Vector2<T>&itself, const Vector2<T> &b) {
            itself.x /= b.x;
            itself.y /= b.y;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> &operator+=(Vector2<T>&itself, const Vector2<T> &b) {
            itself.x += b.x;
            itself.y += b.y;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> &operator-=(Vector2<T>&itself, const Vector2<T> &b) {
            itself.x -= b.x;
            itself.y -= b.y;
            return itself;
        }

        /**
        \brief Returns the norm of the sl::Vector2.
         */
        inline _FCT_CPU_GPU_ float norm() {
            return sqrt(this->x * this->x + this->y * this->y);
        }

        /**
        \brief Returns the squared norm of the sl::Vector2.
         */
        inline _FCT_CPU_GPU_ float square() {
            return (this->x * this->x + this->y * this->y);
        }

        /**
        \brief Returns the sum of the components of the sl::Vector2.
         */
        inline _FCT_CPU_GPU_ float sum() {
            return (this->x + this->y);
        }

        /**
        \brief Returns the dot product of two sl::Vector2.
         */
        static inline _FCT_CPU_GPU_ float dot(const Vector2<T> &a, const Vector2<T> &b) {
            return (a.x * b.x + a.y * b.y);
        }

        /**
        \brief Returns the distance between two sl::Vector2.
         */
        static inline _FCT_CPU_GPU_ float distance(const Vector2<T> &a, const Vector2<T> &b) {
            return sqrt(pow(a.x - b.x, static_cast<T> (2)) + pow(a.y - b.y, static_cast<T> (2)));
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b) {
            Vector2<T> tmp(a);
            return tmp += b;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b) {
            Vector2<T> tmp(a);
            return tmp -= b;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> operator*(const Vector2<T> &a, T b) {
            Vector2<T> tmp(a);
            return tmp *= b;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> operator*(const Vector2<T> &a, const Vector2<T> &b) {
            Vector2<T> tmp(a);
            return tmp *= b;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> operator/(const Vector2<T> &a, T b) {
            Vector2<T> tmp(a);
            return tmp /= b;
        }

        inline _FCT_CPU_GPU_ friend Vector2<T> operator/(const Vector2<T> &a, const Vector2<T> &b) {
            Vector2<T> tmp(a);
            return tmp /= b;
        }
    };

    /**
    \class Vector3
    \ingroup Core_group
    \brief Class representing a 3-dimensional vector for both CPU and GPU.
     */
    template <typename T>
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ Vector3 {
        static const int nbElem = 3;
    public:
        /// @cond

        union {

            struct {
                T x, y, z;
            };

            struct {
                T r, g, b;
            };

            struct {
                T tx, ty, tz;
            };
            T v[nbElem];
        };
        /// @endcond

        /**
        \brief Return the size of the sl::Vector3.
        \return 3
        */
        inline _FCT_CPU_GPU_ int size() const {
            return nbElem;
        }

        /**
        \brief Default constructor.

        Initialize the sl::Vector3 to 0.
        */
        _FCT_CPU_GPU_ Vector3() : x(0), y(0), z(0) {
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector3 to ( \b t, \b t, \b t ).
        */
        _FCT_CPU_GPU_ Vector3(const T &t) {
            this->x = t;
            this->y = t;
            this->z = t;
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector3 with the component of the argument.
        */
        _FCT_CPU_GPU_ Vector3(const T *tp) {
            this->x = tp[0];
            this->y = tp[1];
            this->z = tp[2];
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector3 to ( \b v0, \b v1, \b v2 ).
        */
        _FCT_CPU_GPU_ Vector3(const T v0, const T v1, const T v2) {
            this->x = v0;
            this->y = v1;
            this->z = v2;
        }

        /**
        \brief Copy constructor.

        Initialize the sl::Vector3 by copying another sl::Vector3.
        */
        _FCT_CPU_GPU_ Vector3<T>(const Vector3<T> &v) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector3 with a sl::Vector2 and a scalar (for the third component).
        */
        _FCT_CPU_GPU_ Vector3<T>(const Vector2<T> &v, const T d = 0) {
            this->x = v.x;
            this->y = v.y;
            this->z = d;
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector3 with the first three components of a sl::Vector4.
        */
        _FCT_CPU_GPU_ Vector3<T>(const Vector4<T>& v) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }

        /**
        \brief Returns a pointer of the first component.
        */
        _FCT_CPU_GPU_ const T *ptr() const {
            return &this->v[0];
        }

        /**
        \brief Sets the components of the sl::Vector3 to the values of the argument.
        */
        inline _FCT_CPU_GPU_ Vector3<T> &setValues(const T *b) {
            this->x = b[0];
            this->y = b[1];
            this->z = b[2];
            return *this;
        }

        /**
        \brief Test the equality of the sl::Vector3 with the first three components of a sl::Vector4.
        */
        inline _FCT_CPU_GPU_ Vector3<T>& operator=(const Vector4<T>& other) {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
            return *this;
        }

        /**
        \brief Returns the \b i-th component.
        */
        _FCT_CPU_GPU_ T &operator[](int i) {
            return this->v[i];
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> &operator+=(Vector3<T>&itself, T d) {
            itself.x += d;
            itself.y += d;
            itself.z += d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> &operator+=(Vector3<T>&itself, const Vector3<T> &b) {
            itself.x += b.x;
            itself.y += b.y;
            itself.z += b.z;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> &operator-=(Vector3<T>&itself, T d) {
            itself.x -= d;
            itself.y -= d;
            itself.z -= d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> &operator-=(Vector3<T>&itself, const Vector3<T> &b) {
            itself.x -= b.x;
            itself.y -= b.y;
            itself.z -= b.z;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> &operator*=(Vector3<T>&itself, T d) {
            itself.x *= d;
            itself.y *= d;
            itself.z *= d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> &operator*=(Vector3<T>&itself, const Vector3<T> &b) {
            itself.x *= b.x;
            itself.y *= b.y;
            itself.z *= b.z;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> &operator*=(Vector3<T> &itself, const Matrix3f &b) {
            Vector3<T> tmp(itself);
            itself.v[0] = tmp.v[0] * b.r[0] + tmp.v[1] * b.r[1] + tmp.v[2] * b.r[2];
            itself.v[1] = tmp.v[0] * b.r[3] + tmp.v[1] * b.r[4] + tmp.v[2] * b.r[5];
            itself.v[2] = tmp.v[0] * b.r[6] + tmp.v[1] * b.r[7] + tmp.v[2] * b.r[8];
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> &operator/=(Vector3<T>&itself, T d) {
            if (d == 0) return itself;
            itself.x /= d;
            itself.y /= d;
            itself.z /= d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> &operator/=(Vector3<T>&itself, const Vector3<T> &b) {
            if (b.x != 0) itself.x /= b.x;
            if (b.y != 0) itself.y /= b.y;
            if (b.z != 0) itself.z /= b.z;
            return itself;
        }

        /**
        \brief Returns the norm of the sl::Vector3.
         */
        inline _FCT_CPU_GPU_ float norm() {
            return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        }

        /**
        \brief Returns the squared norm of the sl::Vector3.
         */
        inline _FCT_CPU_GPU_ float square() {
            return (this->x * this->x + this->y * this->y + this->z * this->z);
        }

        /**
        \brief Returns the sum of the components of the sl::Vector3.
         */
        inline _FCT_CPU_GPU_ float sum() {
            return (this->x + this->y + this->z);
        }

        /**
        \brief Returns the dot product of two sl::Vector3.
         */
        static inline _FCT_CPU_GPU_ float dot(const Vector3<T> &a, const Vector3<T> &b) {
            return (a.x * b.x + a.y * b.y + a.z * b.z);
        }

        /**
        \brief Returns the distance between two sl::Vector3.
         */
        static inline _FCT_CPU_GPU_ float distance(const Vector3<T> &a, const Vector3<T> &b) {
            return sqrt(pow(a.x - b.x, static_cast<T> (2)) + pow(a.y - b.y, static_cast<T> (2)) + pow(a.z - b.z, static_cast<T> (2)));
        }

        /**
        \brief Returns the cross product between two sl::Vector3.
         */
        static inline _FCT_CPU_GPU_ Vector3<T> cross(const Vector3<T> &a, const Vector3<T> &b) {
            Vector3<T> r;
            r.x = a.y * b.z - a.z * b.y;
            r.y = a.z * b.x - a.x * b.z;
            r.z = a.x * b.y - a.y * b.x;
            return r;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b) {
            Vector3<T> tmp(a);
            return tmp += b;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b) {
            Vector3<T> tmp(a);
            return tmp -= b;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> operator*(const Vector3<T> &a, T b) {
            Vector3<T> tmp(a);
            return tmp *= b;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> operator*(T a, const Vector3<T> &b) {
            Vector3<T> tmp(a);
            return tmp *= b;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> operator*(const Vector3<T> &a, const Vector3<T> &b) {
            Vector3<T> tmp(a);
            return tmp *= b;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> operator*(const Vector3<T> &a, const Matrix3f &b) {
            Vector3<T> tmp;
            tmp.v[0] = a.v[0] * b.r[0] + a.v[1] * b.r[1] + a.v[2] * b.r[2];
            tmp.v[1] = a.v[0] * b.r[3] + a.v[1] * b.r[4] + a.v[2] * b.r[5];
            tmp.v[2] = a.v[0] * b.r[6] + a.v[1] * b.r[7] + a.v[2] * b.r[8];
            return tmp;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> operator/(const Vector3<T> &a, T b) {
            Vector3<T> tmp(a);
            return tmp /= b;
        }

        inline _FCT_CPU_GPU_ friend Vector3<T> operator/(const Vector3<T> &a, const Vector3<T> &b) {
            Vector3<T> tmp(a);
            return tmp /= b;
        }
    };

    /**
    \class Vector4
    \ingroup Core_group
    \brief Class representing a 4-dimensional vector for both CPU and GPU.
     */
    template <typename T>
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ Vector4 {
        static const int nbElem = 4;
    public:
        /// @cond

        union {

            struct {
                T x, y, z, w;
            };

            struct {
                T r, g, b, a;
            };

            struct {
                T ox, oy, oz, ow;
            };
            T v[nbElem];
        };
        /// @endcond

        /**
        \brief Return the size of the sl::Vector4.
        \return 4
        */
        inline _FCT_CPU_GPU_ int size() const {
            return nbElem;
        }

        /**
        \brief Default constructor.

        Initialize the sl::Vector4 to 0.
        */
        _FCT_CPU_GPU_ Vector4() : x(0), y(0), z(0), w(0) {
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector4 to ( \b t, \b t, \b t, \b t ).
        */
        _FCT_CPU_GPU_ Vector4(const T &t) {
            this->x = t;
            this->y = t;
            this->z = t;
            this->w = t;
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector4 with the component of the argument.
        */
        _FCT_CPU_GPU_ Vector4(const T *tp) {
            this->x = tp[0];
            this->y = tp[1];
            this->z = tp[2];
            this->w = tp[3];
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector4 to ( \b v0, \b v1, \b v2, \b v3 ).
        */
        _FCT_CPU_GPU_ Vector4(const T v0, const T v1, const T v2, const T v3) {
            this->x = v0;
            this->y = v1;
            this->z = v2;
            this->w = v3;
        }

        /**
        \brief Copy constructor.

        Initialize the sl::Vector4 by copying another sl::Vector4.
        */
        _FCT_CPU_GPU_ Vector4<T>(const Vector4<T> &v) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            this->w = v.w;
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector4 with the first three components of a sl::Vector4 and a scalar (for the forth component).
        */
        _FCT_CPU_GPU_ Vector4<T>(const Vector4<T> &v, const T d) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            this->w = d;
        }

        /**
        \brief Constructor.

        Initialize the sl::Vector4 with a sl::Vector3 and a scalar (for the forth component).
        */
        _FCT_CPU_GPU_ Vector4<T>(const Vector3<T>& v, const T d = 0) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            this->w = d;
        }

        /**
        \brief Returns a pointer of the first component.
        */
        _FCT_CPU_GPU_ const T *ptr() const {
            return &this->v[0];
        }

        /**
        \brief Sets the components of the sl::Vector1 to the values of the argument.
        */
        inline _FCT_CPU_GPU_ Vector4<T> &setValues(const T *b) {
            this->x = b[0];
            this->y = b[1];
            this->z = b[2];
            this->w = b[3];
            return *this;
        }

        /**
        \brief Test the equality of the first three components of the sl::Vector4 with a sl::Vector3.
        */
        inline _FCT_CPU_GPU_ Vector4<T>& operator=(const Vector3<T>& other) {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
            return *this;
        }

        /**
        \brief Returns the \b i-th component.
        */
        _FCT_CPU_GPU_ T &operator[](int i) {
            return this->v[i];
        }

        /**
        \brief Returns the \b i-th component.
        */
        _FCT_CPU_GPU_ const T &operator[](int i) const {
            return this->v[i];
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> &operator+=(Vector4<T>&itself, T d) {
            itself.x += d;
            itself.y += d;
            itself.z += d;
            itself.w += d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> &operator+=(Vector4<T>&itself, const Vector4<T> &b) {
            itself.x += b.x;
            itself.y += b.y;
            itself.z += b.z;
            itself.w += b.w;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> &operator-=(Vector4<T>&itself, T d) {
            itself.x -= d;
            itself.y -= d;
            itself.z -= d;
            itself.w -= d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> &operator-=(Vector4<T>&itself, const Vector4<T> &b) {
            itself.x -= b.x;
            itself.y -= b.y;
            itself.z -= b.z;
            itself.w -= b.w;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> &operator*=(Vector4<T>&itself, T d) {
            itself.x *= d;
            itself.y *= d;
            itself.z *= d;
            itself.w *= d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> &operator*=(Vector4<T>&itself, const Vector4<T> &b) {
            itself.x *= b.x;
            itself.y *= b.y;
            itself.z *= b.z;
            itself.w *= b.w;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> &operator*=(Vector4<T> &itself, const Matrix4f &b) {
            Vector4<T> tmp(itself);
            itself.v[0] = tmp.v[0] * b.m[0] + tmp.v[1] * b.m[1] + tmp.v[2] * b.m[2] + tmp.v[3] * b.m[3];
            itself.v[1] = tmp.v[0] * b.m[4] + tmp.v[1] * b.m[5] + tmp.v[2] * b.m[6] + tmp.v[3] * b.m[7];
            itself.v[2] = tmp.v[0] * b.m[8] + tmp.v[1] * b.m[9] + tmp.v[2] * b.m[10] + tmp.v[3] * b.m[11];
            itself.v[3] = tmp.v[0] * b.m[12] + tmp.v[1] * b.m[13] + tmp.v[2] * b.m[14] + tmp.v[3] * b.m[15];
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> &operator/=(Vector4<T>&itself, T d) {
            if (d == 0) return itself;
            itself.x /= d;
            itself.y /= d;
            itself.z /= d;
            itself.w /= d;
            return itself;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> &operator/=(Vector4<T>&itself, const Vector4<T> &b) {
            if (b.x != 0) itself.x /= b.x;
            if (b.y != 0) itself.y /= b.y;
            if (b.z != 0) itself.z /= b.z;
            if (b.w != 0) itself.w /= b.w;
            return itself;
        }

        /**
        \brief Returns the norm of the sl::Vector4.
         */
        inline _FCT_CPU_GPU_ float norm() {
            return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
        }

        /**
        \brief Returns the squared norm of the sl::Vector4.
         */
        inline _FCT_CPU_GPU_ float square() {
            return (this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
        }

        /**
        \brief Returns the sum of the components of the sl::Vector4.
         */
        inline _FCT_CPU_GPU_ float sum() {
            return (this->x + this->y + this->z + this->w);
        }

        /**
        \brief Returns the dot product of two sl::Vector4.
         */
        static inline _FCT_CPU_GPU_ float dot(const Vector4<T> &a, const Vector4<T> &b) {
            return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
        }

        /**
        \brief Returns the distance between two sl::Vector4.
         */
        static inline _FCT_CPU_GPU_ float distance(const Vector4<T> &a, const Vector4<T> &b) {
            return sqrt(pow(a.x - b.x, static_cast<T> (2)) + pow(a.y - b.y, static_cast<T> (2)) + pow(a.z - b.z, static_cast<T> (2)) + pow(a.w - b.w, static_cast<T> (2)));
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> operator-(const Vector4<T> &b) {
            Vector4<T> tmp;
            tmp.x = -b.x;
            tmp.y = -b.y;
            tmp.z = -b.z;
            tmp.w = -b.w;
            return tmp;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> operator+(const Vector4<T> &a, const Vector4<T> &b) {
            Vector4<T> tmp(a);
            return tmp += b;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> operator-(const Vector4<T> &a, const Vector4<T> &b) {
            Vector4<T> tmp(a);
            return tmp -= b;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> operator*(const Vector4<T> &a, T b) {
            Vector4<T> tmp(a);
            return tmp *= b;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> operator*(T a, const Vector4<T> &b) {
            Vector4<T> tmp(a);
            return tmp *= b;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> operator*(const Vector4<T> &a, const Vector4<T> &b) {
            Vector4<T> tmp(a);
            return tmp *= b;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> operator*(const Vector4<T> &a, const Matrix4f &b) {
            Vector4<T> tmp;
            tmp.v[0] = a.v[0] * b.m[0] + a.v[1] * b.m[1] + a.v[2] * b.m[2] + a.v[3] * b.m[3];
            tmp.v[1] = a.v[0] * b.m[4] + a.v[1] * b.m[5] + a.v[2] * b.m[6] + a.v[3] * b.m[7];
            tmp.v[2] = a.v[0] * b.m[8] + a.v[1] * b.m[9] + a.v[2] * b.m[10] + a.v[3] * b.m[11];
            tmp.v[3] = a.v[0] * b.m[12] + a.v[1] * b.m[13] + a.v[2] * b.m[14] + a.v[3] * b.m[15];
            return tmp;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> operator/(const Vector4<T> &a, T b) {
            Vector4<T> tmp(a);
            return tmp /= b;
        }

        inline _FCT_CPU_GPU_ friend Vector4<T> operator/(const Vector4<T> &a, const Vector4<T> &b) {
            Vector4<T> tmp(a);
            return tmp /= b;
        }
    };

    ///@{
    ///  @name Types definition

#ifndef float1
    typedef float float1;
#endif

#ifndef float2
    typedef Vector2<float> float2;
#endif

#ifndef float3
    typedef Vector3<float> float3;
#endif

#ifndef float4
    typedef Vector4<float> float4;
#endif

#ifndef uchar1
    typedef unsigned char uchar1;
#endif

#ifndef uchar2
    typedef Vector2<unsigned char> uchar2;
#endif

#ifndef uchar3
    typedef Vector3<unsigned char> uchar3;
#endif

#ifndef uchar4
    typedef Vector4<unsigned char> uchar4;
#endif

#ifndef double1
    typedef double double1;
#endif

#ifndef double2
    typedef Vector2<double> double2;
#endif

#ifndef double3
    typedef Vector3<double> double3;
#endif

#ifndef double4
    typedef Vector4<double> double4;
#endif

#ifndef uint1
    typedef unsigned int uint1;
#endif

#ifndef uint2
    typedef Vector2<unsigned int> uint2;
#endif

#ifndef uint3
    typedef Vector3<unsigned int> uint3;
#endif

#ifndef uint4
    typedef Vector4<unsigned int> uint4;
#endif

#ifndef ushort1
    typedef unsigned short ushort1;
#endif

#ifndef char4
    typedef Vector4<char> char4;
#endif

    /**
    \ingroup Core_group
    \brief Structure representing timestamps with  utilities.
     */
    struct Timestamp {
        /**
        \brief Timestamp in nanoseconds.
         */
        uint64_t data_ns = 0;

        /**
        \brief Default constructor.
        
        Initialized the sl::Timestamp instance to 0.
         */
        Timestamp() {
        }

        /**
        \brief Initialized the sl::Timestamp instance to a number in nanoseconds.
         */
        Timestamp(uint64_t _data_ns) : data_ns(_data_ns) {
        }

        /**
        \brief Returns the timestamp in nanoseconds.
         */
        inline uint64_t getNanoseconds() {
            return data_ns;
        }

        /**
        \brief Returns the timestamp in microseconds.
         */
        inline uint64_t getMicroseconds() {
            return data_ns / 1000ULL;
        }

        /**
        \brief Returns the timestamp in milliseconds.
         */
        inline uint64_t getMilliseconds() {
            return data_ns / 1000000ULL;
        }

        /**
        \brief Returns the timestamp in seconds.
         */
        inline uint64_t getSeconds() {
            return data_ns / 1000000000ULL;
        }

        /**
        \brief Sets the timestamp to a value in nanoseconds.
         */
        inline void setNanoseconds(uint64_t t_ns) {
            data_ns = t_ns;
        }

        /**
        \brief Sets the timestamp to a value in microseconds.
         */
        inline void setMicroseconds(uint64_t t_us) {
            data_ns = t_us * 1000ULL;
        }

        /**
        \brief Sets the timestamp to a value in milliseconds.
         */
        inline void setMilliseconds(uint64_t t_ms) {
            data_ns = t_ms * 1000000ULL;
        }

        /**
        \brief Sets the timestamp to a value in seconds.
         */
        inline void setSeconds(uint64_t t_s) {
            data_ns = t_s * 1000000000ULL;
        }

        /**
        \brief Copy the value of another sl::Timestamp.
         */
        Timestamp& operator=(Timestamp other) {
            std::swap(data_ns, other.data_ns);
            return *this;
        }

        /**
        \brief Sets the value of the sl::Timestamp to \b other_data_ns.
         */
        Timestamp& operator=(uint64_t other_data_ns) {
            std::swap(data_ns, other_data_ns);
            return *this;
        }

        /**
        \brief Adds the value of another sl::Timestamp to the current one.
         */
        Timestamp& operator+=(const Timestamp& rhs) {
            this->data_ns = this->data_ns + rhs.data_ns;
            return *this;
        }

        /**
        \brief Subtracts the value of another sl::Timestamp to the current one.
         */
        Timestamp& operator-=(const Timestamp& rhs) {
            this->data_ns = this->data_ns - rhs.data_ns;
            return *this;
        }

        /**
        \brief Multiplies the value of another sl::Timestamp to the current one.
         */
        Timestamp& operator*=(const Timestamp& rhs) {
            this->data_ns = this->data_ns * rhs.data_ns;
            return *this;
        }

        /**
        \brief Divides the value of the current sl::Timestamp by another one.
         */
        Timestamp& operator/=(const Timestamp& rhs) {
            this->data_ns = this->data_ns / rhs.data_ns;
            return *this;
        }

        /**
        \brief Convert the sl::Timestamp into a unsigned long long int. 
        */
        operator unsigned long long int() const {
            return static_cast<unsigned long long int> (data_ns);
        }
    };

    inline bool operator<(const Timestamp& lhs, const Timestamp& rhs) {
        return lhs.data_ns < rhs.data_ns; // keep the same order
    }

    inline bool operator>(const Timestamp& lhs, const Timestamp& rhs) {
        return rhs < lhs;
    }

    inline bool operator<=(const Timestamp& lhs, const Timestamp& rhs) {
        return !(lhs > rhs);
    }

    inline bool operator>=(const Timestamp& lhs, const Timestamp& rhs) {
        return !(lhs < rhs);
    }

    inline bool operator==(const Timestamp& lhs, const Timestamp& rhs) {
        return lhs.data_ns == rhs.data_ns;
    }

    inline bool operator!=(const Timestamp& lhs, const Timestamp& rhs) {
        return !(lhs == rhs);
    }

    inline Timestamp operator+(Timestamp lhs, const Timestamp& rhs) {
        lhs += rhs;
        return lhs;
    }

    inline Timestamp operator-(Timestamp lhs, const Timestamp& rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline Timestamp operator/(Timestamp lhs, const Timestamp& rhs) {
        lhs /= rhs;
        return lhs;
    }

    inline Timestamp operator*(Timestamp lhs, const Timestamp& rhs) {
        lhs *= rhs;
        return lhs;
    }
    ///@}

    /// @cond

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Vector2<T> &v2) {
        os << v2.x << " " << v2.y;
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Vector3<T> &v3) {
        os << v3.x << " " << v3.y << " " << v3.z;
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Vector4<T> &v4) {
        os << v4.x << " " << v4.y << " " << v4.z << " " << v4.w;
        return os;
    }

    /**
    \ingroup Core_group
    \brief Returns the current timestamp at the time the function is called. Can be compared to  sl::Camera::getCameraTimestamp for synchronization.

    Use this function to compare the current timestamp and the camera timestamp, since they have the same reference (Computer start time).
    \return The current timestamp in ns.
     */
    static inline Timestamp getCurrentTimeStamp() {
        Timestamp current_ts = 0ULL;
        current_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        return current_ts;
    }


#ifndef ZEDcudaSafeCall
#define ZEDcudaSafeCall(err) __cudaSafeCall(err, __CUSTOM__PRETTY__FUNC__, __FILENAME__, __LINE__)

    static inline cudaError __cudaSafeCall(cudaError err, const char *func, const char *file, const int line) {
        if (err != cudaSuccess)
            printf("in %s : Err [%d]: %s.\n", func, err, cudaGetErrorString(err));
        return err;
    }
#endif

#define TIMING
#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER start = std::chrono::high_resolution_clock::now();
#define DEF_START_TIMER auto start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER(name) std::cout << name << " " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms " << std::endl;
#else
#define INIT_TIMER
#define START_TIMER
#define DEF_START_TIMER
#define STOP_TIMER(name)
#endif
    /// @endcond
}
#endif /* __TYPES_HPP__ */
#ifndef __CORE_HPP__
#define __CORE_HPP__


namespace sl {

    // Avoid conflict with Darknet GPU macro and MEM::GPU enum
#ifdef GPU
#undef GPU
#endif

    /**
    \enum MEM
    \ingroup Core_group
    \brief Lists available memory type.
     */
    enum class MEM {
        CPU = 1, /**< Data will be stored on the CPU (processor side).*/
        GPU = 2 /**< Data will be stored on the GPU (graphic card side).*/
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const MEM &mem);

    inline std::ostream &operator<<(std::ostream &os, const MEM &mem) {
        return os << toString(mem);
    }

    inline MEM operator|(MEM a, MEM b) {
        return static_cast<MEM> (static_cast<int> (a) | static_cast<int> (b));
    }
    ///@endcond

    /**
    \enum COPY_TYPE
    \ingroup Core_group
    \brief Lists available copy operation on sl::Mat.
     */
    enum class COPY_TYPE {
        CPU_CPU, /**< Copy data from CPU to CPU.*/
        CPU_GPU, /**< Copy data from CPU to GPU.*/
        GPU_GPU, /**< Copy data from GPU to GPU.*/
        GPU_CPU /**< Copy data from GPU to CPU.*/
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const COPY_TYPE &cpy);

    inline std::ostream &operator<<(std::ostream &os, const COPY_TYPE &cpy) {
        return os << toString(cpy);
    }
    ///@endcond

    /**
    \enum MAT_TYPE
    \ingroup Core_group
    \brief Lists available sl::Mat formats.
    \note sl::Mat type depends on image or measure type.
    \note For the dependencies, see sl::VIEW and sl::MEASURE.
     */
    enum class MAT_TYPE {
        F32_C1, /**< 1-channel matrix of float*/
        F32_C2, /**< 2-channel matrix of float*/
        F32_C3, /**< 3-channel matrix of float*/
        F32_C4, /**< 4-channel matrix of float*/
        U8_C1, /**< 1-channel matrix of unsigned char*/
        U8_C2, /**< 2-channel matrix of unsigned char*/
        U8_C3, /**< 3-channel matrix of unsigned char*/
        U8_C4, /**< 4-channel matrix of unsigned char*/
        U16_C1, /**< 1-channel matrix of unsigned short*/
        S8_C4 /**< 4-channel matrix of signed char*/
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const MAT_TYPE &type);

    inline std::ostream &operator<<(std::ostream &os, const MAT_TYPE &type) {
        return os << toString(type);
    }
    ///@endcond

    /**
    \class Mat
    \ingroup Core_group
    \brief Class representing 1 to 4-channel matrix of float or uchar, stored on CPU and/or GPU side.

    This class is defined in a row-major order, meaning that for an image buffer, the rows are stored consecutively from top to bottom.

    The CPU and GPU buffer aren't automatically synchronized for performance reasons, you can use \ref updateCPUfromGPU / \ref updateGPUfromCPU to do it.
    \n If you are using the GPU side of the sl::Mat object, you need to make sure to call \ref free before destroying the sl::Camera object.
    \n The destruction of the sl::Camera object deletes the CUDA context needed to free the GPU sl::Mat memory.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Mat {
    private:
        //  Array size.
        Resolution size;

        // Number of values by pixels.
        size_t channels = 0;

        // GPU Step of the Mat in Bytes.
        size_t step_gpu = 0;

        // CPU Step of the Mat in Bytes.
        size_t step_cpu = 0;

        // size in bytes of one pixel
        size_t pixel_bytes = 0;

        // Data format.
        MAT_TYPE data_type;

        // Type of allocated memory.
        MEM mem_type = MEM::CPU;

        // Pointer to memory on HOST/CPU, if available.
        uchar1 *ptr_cpu = NULL;

        // Pointer to memory on DEVICE/GPU, if available.
        uchar1 *ptr_gpu = NULL;

        // Defines if the Mat is initialized.
        bool init = false;

        // Defines if the memory is owned (and thus freed) or shared.
        bool memory_owner = false;

        //private
        void ref(const Mat &mat);

    public:
        /**
        \brief Variable used in verbose mode to indicate which sl::Mat is printing informations.

        Default set to "n/a" to avoid empty string if not filled.
         */
        String name = "n/a";

        /**
        \brief Whether the sl::Mat can display informations.
         */
        bool verbose = false;

        /**
        \brief Timestamp of the last manipulation of the data of the matrix by a method/function.
         */
        Timestamp timestamp = 0;

        /**
        \brief Default constructor.

        The sl::Mat is empty (width = height = 0).
         */
        Mat();

        /**
        \brief Constructor.

        Initializes the sl::Mat and allocates the requested memory by calling \ref alloc().

        \param width : Width of the matrix in pixels.
        \param height : Height of the matrix in pixels.
        \param mat_type : Type of the matrix ([sl::MAT_TYPE::F32_C1](\ref MAT_TYPE), [sl::MAT_TYPE::U8_C4](\ref MAT_TYPE), etc.).
        \param memory_type : Where the buffer will be stored ([sl::MEM::CPU](\ref MEM) and/or [sl::MEM::GPU](\ref MEM)).
         */
        Mat(size_t width, size_t height, MAT_TYPE mat_type, MEM memory_type = MEM::CPU);

        /**
        \brief Constructor from an existing data pointer.

        Initializes the sl::Mat but does not allocate the memory.

        \param width : Width of the matrix in pixels.
        \param height : Height of the matrix in pixels.
        \param mat_type : Type of the matrix ([sl::MAT_TYPE::F32_C1](\ref MAT_TYPE), [sl::MAT_TYPE::U8_C4](\ref MAT_TYPE), etc.).
        \param ptr : Pointer to the data array (CPU or GPU).
        \param step : Step of the data array (bytes size of one pixel row).
        \param memory_type : Where the buffer will be stored ([sl::MEM::CPU](\ref MEM) and/or [sl::MEM::GPU](\ref MEM)).
         */
        Mat(size_t width, size_t height, MAT_TYPE mat_type, sl::uchar1 *ptr, size_t step, MEM memory_type = MEM::CPU);

        /**
        \brief Constructor from two existing data pointers, CPU and GPU.

        Initializes the sl::Mat but does not allocate the memory.

        \param width : Width of the matrix in pixels.
        \param height : Height of the matrix in pixels.
        \param mat_type : Type of the matrix ([sl::MAT_TYPE::F32_C1](\ref MAT_TYPE), [sl::MAT_TYPE::U8_C4](\ref MAT_TYPE), etc.).
        \param ptr_cpu : CPU pointer to the data array.
        \param step_cpu : Step of the CPU data array (bytes size of one pixel row).
        \param ptr_gpu : GPU pointer to the data array.
        \param step_gpu : Step of the GPU data array (bytes size of one pixel row).
         */
        Mat(size_t width, size_t height, MAT_TYPE mat_type, sl::uchar1 *ptr_cpu, size_t step_cpu, sl::uchar1 *ptr_gpu, size_t step_gpu);

        /**
        \brief Constructor from an sl::Resolution.

        Initializes the sl::Mat and allocates the requested memory by calling \ref alloc().

        \param resolution : Size of the matrix in pixels.
        \param mat_type : Type of the matrix ([sl::MAT_TYPE::F32_C1](\ref MAT_TYPE), [sl::MAT_TYPE::U8_C4](\ref MAT_TYPE), etc.).
        \param memory_type : Where the buffer will be stored ([sl::MEM::CPU](\ref MEM) and/or [sl::MEM::GPU](\ref MEM)).
         */
        Mat(Resolution resolution, MAT_TYPE mat_type, MEM memory_type = MEM::CPU);

        /**
        \brief Constructor from an existing data pointer.

        Initializes the sl::Mat but does not allocate the memory.

        \param resolution : Size of the matrix in pixels.
        \param mat_type : Type of the matrix ([sl::MAT_TYPE::F32_C1](\ref MAT_TYPE), [sl::MAT_TYPE::U8_C4](\ref MAT_TYPE), etc.).
        \param ptr : Pointer to the data array (CPU or GPU).
        \param step : Step of the data array (bytes size of one pixel row).
        \param memory_type : Where the buffer will be stored ([sl::MEM::CPU](\ref MEM) and/or [sl::MEM::GPU](\ref MEM)).
         */
        Mat(Resolution resolution, MAT_TYPE mat_type, sl::uchar1 *ptr, size_t step, MEM memory_type = MEM::CPU);

        /**
        \brief Constructor from two existing data pointers, CPU and GPU.

        Initializes the sl::Mat but does not allocate the memory.

        \param resolution : Size of the matrix in pixels.
        \param mat_type : Type of the matrix ([sl::MAT_TYPE::F32_C1](\ref MAT_TYPE), [sl::MAT_TYPE::U8_C4](\ref MAT_TYPE), etc.).
        \param ptr_cpu : CPU pointer to the data array.
        \param step_cpu : Step of the CPU data array (bytes size of one pixel row).
        \param ptr_gpu : GPU pointer to the data array.
        \param step_gpu : Step of the GPU data array (bytes size of one pixel row).
         */
        Mat(Resolution resolution, MAT_TYPE mat_type, sl::uchar1 *ptr_cpu, size_t step_cpu, sl::uchar1 *ptr_gpu, size_t step_gpu);

        /**
        \brief Copy constructor (shallow copy).

        Initializes the sl::Mat but does not allocate the memory.

        \param mat : Reference to the sl::Mat to copy.
         */
        Mat(const Mat &mat);

        /**
        \brief Allocates the sl::Mat memory.
        \param width : Width of the matrix in pixels.
        \param height : Height of the matrix in pixels.
        \param mat_type : Type of the matrix ([sl::MAT_TYPE::F32_C1](\ref MAT_TYPE), [sl::MAT_TYPE::U8_C4](\ref MAT_TYPE), etc.).
        \param memory_type : Where the buffer will be stored ([sl::MEM::CPU](\ref MEM) and/or [sl::MEM::GPU](\ref MEM)).

        \warning It erases previously allocated memory.
         */
        void alloc(size_t width, size_t height, MAT_TYPE mat_type, MEM memory_type = MEM::CPU);

        /**
        \brief Allocates the sl::Mat memory.
        \param resolution : Size of the matrix in pixels.
        \param mat_type : Type of the matrix ([sl::MAT_TYPE::F32_C1](\ref MAT_TYPE), [sl::MAT_TYPE::U8_C4](\ref MAT_TYPE), etc.).
        \param memory_type : Where the buffer will be stored ([sl::MEM::CPU](\ref MEM) and/or [sl::MEM::GPU](\ref MEM)).

        \warning It erases previously allocated memory.
         */
        void alloc(Resolution resolution, MAT_TYPE mat_type, MEM memory_type = MEM::CPU);

        /**
        \brief Destructor.
        
        This method calls \ref free to release owned memory.
         */
        ~Mat();

        /**
        \brief Free the owned memory.
        \param memory_type : Specifies whether you want to free the [sl::MEM::CPU](\ref MEM) and/or [sl::MEM::GPU](\ref MEM) memory.
         */
        void free(MEM memory_type = MEM::CPU | MEM::GPU);

        /**
        \brief Performs a shallow copy.

        This method does not copy the data array, it only copies the pointer.

        \param that : sl::Mat to be copied.
        \return The new sl::Mat object which point to the same data as that.
         */
        Mat &operator=(const Mat &that);

        /**
        \brief Downloads data from DEVICE (GPU) to HOST (CPU), if possible.
        \param stream : Specifies the GPU stream to be used to enable asynchronous overlapping. Default: 0 (synchronous)
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.

        \note If no CPU or GPU memory are available for this sl::Mat, some are directly allocated.
        \note If verbose is set to true, you have information in case of failure.
         */
        ERROR_CODE updateCPUfromGPU(cudaStream_t stream = 0);

        /**
        \brief Uploads data from HOST (CPU) to DEVICE (GPU), if possible.
        \param stream : Specifies the GPU stream to be used to enable asynchronous overlapping. Default: 0 (synchronous)
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.

        \note If no CPU or GPU memory are available for this sl::Mat, some are directly allocated.
        \note If verbose is set to true, you have information in case of failure.
         */
        ERROR_CODE updateGPUfromCPU(cudaStream_t stream = 0, int GPU_id = 0);

        /**
        \brief Copies data an other sl::Mat (deep copy).
        \param dst : sl::Mat where the data will be copied.
        \param cpyType : Specifies the memory that will be used for the copy.
        \param stream : Specifies the GPU stream to be used to enable asynchronous overlapping. Default: 0 (synchronous)
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.

        \note If the destination is not allocated or or doesn't have a compatible sl::MAT_TYPE or sl::Resolution,
        current memory is freed and new memory is directly allocated.
         */
        ERROR_CODE copyTo(Mat &dst, COPY_TYPE cpyType = COPY_TYPE::CPU_CPU, cudaStream_t stream = 0) const;

        /**
        \brief Copies data from an other sl::Mat (deep copy).
        \param src : sl::Mat where the data will be copied from.
        \param cpyType : Specifies the memory that will be used for the copy.
        \param stream : Specifies the GPU stream to be used to enable asynchronous overlapping. Default: 0 (synchronous)
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.

        \note If the destination is not allocated or or doesn't have a compatible sl::MAT_TYPE or sl::Resolution,
        current memory is freed and new memory is directly allocated.
         */
        ERROR_CODE setFrom(const Mat &src, COPY_TYPE cpyType = COPY_TYPE::CPU_CPU, cudaStream_t stream = 0);

        /**
        \brief Reads an image from a file.

        \param filePath : Path of the file to read (including the name and extension).
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.
        
        \note This method only support images such as JPG or PNG, and can't load float format such as PCD, PLY, etc.
         */
        ERROR_CODE read(const String &filePath);

        /**
        \brief Writes the sl::Mat (only if [sl::MEM::CPU](\ref MEM) is available) into a file defined by its extension.
		       
        \param filePath : Path of the file to write in (including the name and extension).
        \param memory_type : Memory type (CPU or GPU) of the sl::Mat.
        \param compression_level : Level of compression between 0 (lowest compression == highest size == highest quality(jpg)) and 100 (highest compression == lowest size == lowest quality(jpg)).
        \note Specific/default value for compression_level = -1 : This will set the default quality for PNG(30) or JPEG(5).
        \note \b compression_level is only supported for U8_Cx sl::MAT_TYPE.
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.

        \note Supported sl::MAT_TYPE are:
        - [sl::MAT_TYPE::F32_C1](\ref MAT_TYPE) for PNG/PFM/PGM
        - [sl::MAT_TYPE::F32_C3](\ref MAT_TYPE) for PCD/PLY/VTK/XYZ
        - [sl::MAT_TYPE::F32_C4](\ref MAT_TYPE) for PCD/PLY/VTK/WYZ
        - [sl::MAT_TYPE::U8_C1](\ref MAT_TYPE) for PNG/JPG
        - [sl::MAT_TYPE::U8_C3](\ref MAT_TYPE) for PNG/JPG
        - [sl::MAT_TYPE::U8_C4](\ref MAT_TYPE) for PNG/JPG
         */
        ERROR_CODE write(const String &filePath, sl::MEM memory_type = sl::MEM::CPU, int compression_level = -1);

        /**
        \brief Fills the sl::Mat with the given value.

        This method overwrites all the matrix.

        \param value : Value to be copied all over the matrix.
        \param memory_type : Which buffer to fill, CPU and/or GPU.
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.

        \note This method is templated for \ref uchar1, \ref uchar2, \ref uchar3, \ref uchar4, \ref float1, \ref float2, \ref float3, \ref float4.
         */
        template <typename T>
        ERROR_CODE setTo(T value, sl::MEM memory_type = MEM::CPU);

        /**
        \brief Sets a value to a specific point in the matrix.
        \param x : Column of the point to change.
        \param y : Row of the point to change.
        \param value : Value to be set.
        \param memory_type : Which memory will be updated.
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.

        \note This method is templated for \ref uchar1, \ref uchar2, \ref uchar3, \ref uchar4, \ref float1, \ref float2, \ref float3, \ref float4.

        \warning Not efficient for [sl::MEM::GPU](\ref MEM), use it on sparse data.
         */
        template <typename N>
        ERROR_CODE setValue(size_t x, size_t y, N value, sl::MEM memory_type = MEM::CPU);

        /**
        \brief Returns the value of a specific point in the matrix.
        \param x : Column of the point to get the value from.
        \param y : Row of the point to get the value from.
        \param memory_type : Which memory should be read.
        \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if everything went well, [sl::ERROR_CODE::FAILURE](\ref ERROR_CODE) otherwise.

        \note This method is templated for \ref uchar1, \ref uchar2, \ref uchar3, \ref uchar4, \ref float1, \ref float2, \ref float3, \ref float4.

        \warning Not efficient for [sl::MEM::GPU](\ref MEM), use it on sparse data.
         */
        template <typename N>
        ERROR_CODE getValue(size_t x, size_t y, N *value, MEM memory_type = MEM::CPU) const;

        /**
        \brief Returns the width of the matrix.
        \return Width of the matrix in pixels.
         */
        inline size_t getWidth() const {
            return size.width;
        }

        /**
        \brief Returns the height of the matrix.
        \return Height of the matrix in pixels.
         */
        inline size_t getHeight() const {
            return size.height;
        }

        /**
        \brief Returns the resolution (width and height) of the matrix.
        \return Resolution of the matrix in pixels.
         */
        inline Resolution getResolution() const {
            return size;
        }

        /**
        \brief Returns the number of values stored in one pixel.
        \return Number of values in a pixel.
         */
        inline size_t getChannels() const {
            return channels;
        }

        /**
        \brief Returns the format of the matrix.
        \return Format of the current sl::Mat.
         */
        inline MAT_TYPE getDataType() const {
            return data_type;
        }

        /**
        \brief Returns the type of memory (CPU and/or GPU).
        \return Type of allocated memory.
         */
        inline MEM getMemoryType() const {
            return mem_type;
        }

        /**
        \brief Returns the CPU or GPU data pointer.
        \param memory_type : Specifies whether you want [sl::MEM::CPU](\ref MEM) or [sl::MEM::GPU](\ref MEM).
        \return The pointer of the Mat data.
         */
        template <typename N>
        N *getPtr(MEM memory_type = MEM::CPU) const;

        /**
        \brief Returns the memory step in bytes (size of one pixel row).
        \param memory_type : Specifies whether you want [sl::MEM::CPU](\ref MEM) or [sl::MEM::GPU](\ref MEM) step.
        \return The step in bytes of the specified memory.
         */
        size_t getStepBytes(MEM memory_type = MEM::CPU) const;

        /**
        \brief Returns the memory step in number of elements (size in one pixel row).
        \param memory_type : Specifies whether you want [sl::MEM::CPU](\ref MEM) or [sl::MEM::GPU](\ref MEM) step.
        \return The step in number of elements.
         */
        template <typename N>
        inline size_t getStep(MEM memory_type = MEM::CPU) const {
            return getStepBytes(memory_type) / sizeof (N);
        }

        /**
        \brief Returns the memory step in number of elements (size in one pixel row).
        \param memory_type : Specifies whether you want [sl::MEM::CPU](\ref MEM) or [sl::MEM::GPU](\ref MEM) step.
        \return The step in number of elements.
         */
        inline size_t getStep(MEM memory_type = MEM::CPU) const {
            switch (data_type) {
                case MAT_TYPE::F32_C1:
                    return getStep<sl::float1>(memory_type);
                case MAT_TYPE::F32_C2:
                    return getStep<sl::float2>(memory_type);
                case MAT_TYPE::F32_C3:
                    return getStep<sl::float3>(memory_type);
                case MAT_TYPE::F32_C4:
                    return getStep<sl::float4>(memory_type);
                case MAT_TYPE::U8_C1:
                    return getStep<sl::uchar1>(memory_type);
                case MAT_TYPE::U8_C2:
                    return getStep<sl::uchar2>(memory_type);
                case MAT_TYPE::U8_C3:
                    return getStep<sl::uchar3>(memory_type);
                case MAT_TYPE::U8_C4:
                    return getStep<sl::uchar4>(memory_type);
                case MAT_TYPE::U16_C1:
                    return getStep<sl::ushort1>(memory_type);
                case MAT_TYPE::S8_C4:
                    return getStep<sl::uchar4>(memory_type);

            }
            return 0;
        }

        /**
        \brief Returns the size of one pixel in bytes.
        \return Size of a pixel in bytes.
         */
        inline size_t getPixelBytes() const {
            return pixel_bytes;
        }

        /**
        \brief Returns the size of a row in bytes.
        \return Size of a row in bytes.
         */
        inline size_t getWidthBytes() const {
            return pixel_bytes * size.width;
        }

        /**
        \brief Returns the information about the sl::Mat into a sl::String.
        \return String containing the sl::Mat information.
         */
        String getInfos();

        /**
        \brief Returns whether the sl::Mat is initialized or not.
        \return True if current sl::Mat has been allocated (by the constructor or therefore).
         */
        inline bool isInit() const {
            return init;
        }

        /**
        \brief Returns whether the sl::Mat is the owner of the memory it accesses.

        If not, the memory won't be freed if the sl::Mat is destroyed.
        \return True if the sl::Mat is owning its memory, else false.
         */
        inline bool isMemoryOwner() const {
            return memory_owner;
        }

        /**
        \brief Duplicates a sl::Mat by copy (deep copy).
        \param src : Reference of the sl::Mat to copy.

        This method copies the data array(s) and it marks the new sl::Mat as the memory owner.
         */
        ERROR_CODE clone(const Mat &src);

        /**
        \brief Moves the data of the sl::Mat to another sl::Mat.

        This method gives the attribute of the current s::Mat to the specified one. (No copy.)
        \param dst : Reference to the sl::Mat to move to.
        \note : The current sl::Mat is then no more usable since its loose its attributes.
         */
        ERROR_CODE move(Mat &dst);

        /**
        \brief Swaps the content of the provided sl::Mat (only swaps the pointers, no data copy).

        This method swaps the pointers of the given sl::Mat.
        \param mat1 : First matrix to swap.
        \param mat2 : Second matrix to swap.
         */
        static void swap(Mat &mat1, Mat &mat2);
    };

    /**
    \brief Convert Image format from Unsigned char to Signed char, designed for Unreal Engine pipeline, works on GPU memory.
    \param image_in : input image to convert
    \param image_signed : output image to converted
    \param stream : a cuda stream to put the compute to (def. 0)
    \note If the Output Mat does not satisfies the requirements, it is freed and re-allocated.
     */
    ERROR_CODE SL_CORE_EXPORT convertImage(sl::Mat &image_in, sl::Mat &image_signed, cudaStream_t stream = 0);

    ///@cond
    class SL_CORE_EXPORT Rotation;
    class SL_CORE_EXPORT Translation;
    class SL_CORE_EXPORT Orientation;
    class SL_CORE_EXPORT Transform;
    ///@endcond

    /**
    \class Rotation
    \ingroup PositionalTracking_group
    \brief Class representing a rotation for the positional tracking module.

    It inherits from the generic sl::Matrix3f class.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Rotation : public Matrix3f {
    public:
        /**
        \brief Default constructor.

        Creates a null rotation.
         */
        Rotation();

        /**
        \brief Copy constructor (deep copy).
        \param rotation : sl::Rotation to copy.
         */
        Rotation(const Rotation &rotation);

        /**
        \brief sl::Rotation constructor from an sl::Matrix3f.

        Copies the sl::Matrix3f (deep copy).
        \param mat : sl::Matrix3f to copy.
         */
        Rotation(const Matrix3f &mat);

        /**
        \brief sl::Rotation constructor from an sl::Orientation.

        It converts the Orientation representation to the Rotation one.
        \param orientation : the Orientation to be used.
         */
        Rotation(const Orientation &orientation);

        /**
        \brief sl::Rotation constructor from an angle and an axis.
        \param angle : Rotation angle in radian.
        \param axis : 3D axis to rotate around.
         */
        Rotation(const float angle, const Translation &axis);

        /**
        \brief Sets the sl::Rotation from an sl::Orientation.
        \param orientation : sl::Orientation containing the rotation to set.
         */
        void setOrientation(const Orientation &orientation);

        /**
        \brief Returns the sl::Orientation corresponding to the current sl::Rotation.
        \return Rotation of the current orientation.
         */
        Orientation getOrientation() const;

        /**
        \brief Returns the 3x1 rotation vector obtained from 3x3 rotation matrix using Rodrigues formula.
        \return Rotation vector created from the sl::Orientation values.
         */
        float3 getRotationVector();

        /**
        \brief Sets the sl::Rotation from a rotation vector (using Rodrigues' transformation).
        \param vec_rot : Vector containing the rotation value for each axis ```(rx, ry, rz)```.
         */
        void setRotationVector(const float3 &vec_rot);

        /**
        \brief Converts the sl::Rotation into Euler angles.
        \param radian : Whether the angle will be returned in radian or degree.
        \return Euler angles created from the sl::Rotation values representing the rotations around the X, Y and Z axes using YZX convention.
         */
        float3 getEulerAngles(bool radian = true) const;

        /**
        \brief Sets the sl::Rotation from Euler angles.
        \param euler_angles : Euler angles (as a sl::float3) to update the sl::Rotation.
        \param radian : Whether the angle is in radian or degree.
         */
        void setEulerAngles(const float3 &euler_angles, bool radian = true);
    };

    /**
    \class Translation
    \ingroup PositionalTracking_group
    \brief Class representing a translation for the positional tracking module.

    sl::Translation is a vector as ```[tx, ty, tz]```.
    \n You can access the data with the 't' ptr or by element name as :
    tx, ty, tz  <-> | 0 1 2 |
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Translation : public float3 {
    public:
        /**
        \brief Default constructor.

        Creates a null translation.
         */
        Translation();

        /**
        \brief Copy constructor (deep copy).
        \param translation : sl::Translation to copy.
         */
        Translation(const Translation &translation);

        /**
        \brief Constructor.
        \param t1 : x component of the translation.
        \param t2 : y component of the translation.
        \param t3 : z component of the translation.
         */
        Translation(float t1, float t2, float t3);

        /**
        \brief Constructor from an sl::float3.
        \param in : sl::float3 to copy.
         */
        Translation(float3 in);

        /**
        \brief Multiplication operator by an Orientation.
        \param mat : Orientation.
        \return The current Translation after being multiplied by the orientation.
         */
        Translation operator*(const Orientation &mat) const;

        /**
        \brief Normalizes the current sl::Translation.
         */
        void normalize();

        /**
        \brief Gets the normalized sl::Translation of a given sl::Translation.
        \param tr : sl::Translation to be get the normalized translation from.
        \return Another sl::Translation object equal to [\b tr.normalize()](\ref normalize).
         */
        static Translation normalize(const Translation &tr);

        /**
        \brief Gets the value at specific position in the sl::Translation.
        \param x : Position of the value.
        \return Value at the x position.
         */
        float &operator()(int x);
    };

    /**
    \class Orientation
    \ingroup PositionalTracking_group
    \brief Class representing an orientation/quaternion for the positional tracking module.

    sl::Orientation is a vector defined as ```[ox, oy, oz, ow]```.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Orientation : public float4 {
    public:
        /**
        \brief Default constructor.

        Creates an identity orientation.
         */
        Orientation();

        /**
        \brief Copy constructor (deep copy).
        \param orientation : sl::Orientation to copy.
         */
        Orientation(const Orientation &orientation);

        /**
        \brief Copy constructor (deep copy).
        \param in : sl::float4 to copy.
         */
        Orientation(const float4 &in);

        /**
        \brief Constructor from an sl::Rotation.

        It converts the sl::Rotation representation to the sl::Orientation one.
        \param rotation : sl::Rotation to be used.
         */
        Orientation(const Rotation &rotation);

        /**
        \brief Constructor from a vector represented by two sl::Translation.
        \param tr1 : First point of the vector.
        \param tr2 : Second point of the vector.
         */
        Orientation(const Translation &tr1, const Translation &tr2);

        /**
        \brief Gets the value at specific position in the sl::Orientation.
        \param x : Position of the value.
        \return Value at the x position.
         */
        float operator()(int x);

        /**
        \brief Multiplication operator by an sl::Orientation.
        \param orientation : sl.Orientation to multiply the current one with.
        \return The result of the multiplication between current sl.Orientation and the one given as input.
         */
        Orientation operator*(const Orientation &orientation) const;

        /**
        \brief Sets the sl::Orientation from an sl::Rotation.
        \param rotation : sl::Rotation to be used.
         */
        void setRotationMatrix(const Rotation &rotation);

        /**
        \brief Returns the current sl::Orientation as an sl::Rotation.
        \return The rotation computed from the orientation data.
         */
        Rotation getRotationMatrix() const;

        /**
        \brief Sets the current sl::Orientation to identity.
         */
        void setIdentity();

        /**
        \brief Creates an sl::Orientation initialized to identity.
        \return Identity sl::Orientation.
         */
        static Orientation identity();

        /**
        \brief Fills the current sl::Orientation with zeros.
         */
        void setZeros();

        /**
        \brief Creates an sl::Orientation filled with zeros.
        \return sl::Orientation filled with zeros.
         */
        static Orientation zeros();

        /**
        \brief Normalizes the current sl::Orientation.
         */
        void normalise();

        /**
        \brief Gets the normalized sl::Orientation of a given sl::Orientation.
        \param orient : sl::Orientation to be get the normalized orientation from.
        \return Another sl::Orientation object equal to [\b orient.normalize()](\ref normalize).
         */
        static Orientation normalise(const Orientation &orient);
    };

    /**
    \class Transform
    \ingroup PositionalTracking_group
    \brief Class representing a transformation (translation and rotation) for the positional tracking module.

    It can be used to create any type of Matrix4x4 or sl::Matrix4f that must be specifically used for handling a rotation and position information (OpenGL, Tracking, etc.).
    \n It inherits from the generic sl::Matrix4f class.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Transform : public Matrix4f {
    public:
        /**
        \brief Default constructor.
         */
        Transform();

        /**
        \brief Copy constructor (deep copy).
         * \param motion : sl::Transform to copy.
         */
        Transform(const Transform &motion);

        /**
        \brief Copy constructor (deep copy).
        \param mat : sl::Matrix4f to copy.
         */
        Transform(const Matrix4f &mat);

        /**
        \brief Constructor from an sl::Rotation and a sl::Translation.
        \param rotation : sl::Rotation to copy.
        \param translation : sl::Translation to copy.
         */
        Transform(const Rotation &rotation, const Translation &translation);

        /**
        \brief Constructor from an sl::Orientation and a sl::Translation.
        \param orientation : sl::Orientation to copy.
        \param translation : sl::Translation to copy.
         */
        Transform(const Orientation &orientation, const Translation &translation);

        /**
        \brief Sets the rotation component of the current sl::Transform from an sl::Rotation.
        \param rotation : sl::Rotation to be used.
         */
        void setRotationMatrix(const Rotation &rotation);

        /**
        \brief Returns the sl::Rotation corresponding to the current sl::Transform.
        \return sl::Rotation created from the sl::Transform values.
        \warning The given sl::Rotation contains a copy of the sl::Transform values. Not references.
         */
        Rotation getRotationMatrix() const;

        /**
        \brief Sets the translation component of the current sl::Transform from an sl::Translation.
        \param translation : sl::Translation to be used.
         */
        void setTranslation(const Translation &translation);

        /**
        \brief Returns the sl::Translation corresponding to the current sl::Transform.
        \return sl::Translation created from the sl::Transform values.
        \warning The given sl::Translation contains a copy of the sl::Transform values. Not references.
         */
        Translation getTranslation() const;

        /**
        \brief Sets the orientation component of the current sl::Transform from an sl::Orientation.
        \param orientation : sl::Orientation to be used.
         */
        void setOrientation(const Orientation &orientation);

        /**
        \brief Returns the sl::Orientation corresponding to the current sl::Transform.
        \return sl::Orientation created from the sl::Transform values.
        \warning The given sl::Orientation contains a copy of the sl::Transform values.
         */
        Orientation getOrientation() const;

        /**
        \brief Returns the 3x1 rotation vector obtained from 3x3 rotation matrix using Rodrigues formula.
        \return Rotation vector created from the sl::Transform values.
         */
        float3 getRotationVector();

        /**
        \brief Sets the rotation component of the sl::Transform with a 3x1 rotation vector (using Rodrigues' transformation).
        \param vec_rot : Vector containing the rotation value for each axis ```(rx, ry, rz)```.
         */
        void setRotationVector(const float3 &vec_rot);

        /**
        \brief Converts the rotation component of the sl::Transform into Euler angles.
        \param radian : Whether the angle will be returned in radian or degree.
        \return Euler angles created from the sl::Transform values as a sl::float3 representing the rotations around the X, Y and Z axes using YZX convention.
         */
        float3 getEulerAngles(bool radian = true) const;

        /**
        \brief Sets the rotation component of the sl::Transform from Euler angles.
        \param euler_angles : Euler angles (as a sl::float3) to update the sl::Transform.
        \param radian : Whether the angle is in radian or degree.
         */
        void setEulerAngles(const float3 &euler_angles, bool radian = true);
    };

    /**
    \struct CameraParameters
    \ingroup Depth_group
    \brief Structure containing the intrinsic parameters of a camera.

    That information about the camera will be returned by sl::Camera.getCameraInformation().
    \note Similar to the sl::CalibrationParameters, those parameters are taken from the settings file (SNXXX.conf) and are modified during the sl::Camera.open() call when running a self-calibration).
    \note Those parameters given after sl::Camera.open() call, represent the camera matrix corresponding to rectified or unrectified images.
    \note When filled with rectified parameters, fx, fy, cx, cy must be the same for left and right camera once sl::Camera.open() has been called.
    \note Since distortion is corrected during rectification, distortion should not be considered on rectified images.
     */
    struct CameraParameters {
        /**
        \brief Focal length in pixels along x axis.
         */
        float fx;

        /**
        \brief Focal length in pixels along y axis.
         */
        float fy;

        /**
        \brief Optical center along x axis, defined in pixels (usually close to width / 2).
         */
        float cx;

        /**
        \brief Optical center along y axis, defined in pixels (usually close to height / 2).
         */
        float cy;

        /**
        \brief Distortion factor : [k1, k2, p1, p2, k3, k4, k5, k6, s1, s2, s3, s4].
        
        Radial (k1, k2, k3, k4, k5, k6), Tangential (p1,p2) and Prism (s1, s2, s3, s4) distortion.
         */
        double disto[12];

        /**
        \brief Vertical field of view, in degrees.
         */
        float v_fov;

        /**
        \brief Horizontal field of view, in degrees.
         */
        float h_fov;

        /**
        \brief Diagonal field of view, in degrees.
         */
        float d_fov;

        /**
        \brief Size in pixels of the images given by the camera.
         */
        Resolution image_size;

        /**
        \brief Real focal length in millimeters.
         */
        float focal_length_metric;

        /**
        \brief Return the sl::CameraParameters for another resolution.
        \param output_resolution : Resolution in which to get the new sl::CameraParameters.
        \return The sl::CameraParameters for the resolution given as input.
         */
        CameraParameters scale(sl::Resolution const& output_resolution) const {
            sl::CameraParameters calib_out = (*this);
            sl::float2 ratio(static_cast<float> (output_resolution.width) / static_cast<float> (image_size.width), static_cast<float> (output_resolution.height) / static_cast<float> (image_size.height));

            calib_out.fx = fx * ratio.x;
            calib_out.fy = fy * ratio.y;
            calib_out.cx = cx * ratio.x;
            calib_out.cy = cy * ratio.y;
            calib_out.image_size = output_resolution;
            memcpy(calib_out.disto, disto, sizeof (disto));

            return calib_out;
        }

    };

    /**
    \struct CalibrationParameters
    \ingroup Depth_group
    \brief Structure containing intrinsic and extrinsic parameters of the camera (translation and rotation).

    That information about the camera will be returned by sl::Camera.getCameraInformation().

    \note The calibration/rectification process, called during sl::Camera.open(), is using the raw parameters defined in the SNXXX.conf file, where XXX is the serial number of the camera.
    \note Those values may be adjusted or not by the self-calibration to get a proper image alignment.
    \note After sl::Camera.open() is done (with or without self-calibration activated), most of the stereo parameters (except baseline of course) should be 0 or very close to 0.
    \note It means that images after rectification process (given by sl::Camera.retrieveImage()) are aligned as if they were taken by a "perfect" stereo camera, defined by the new sl::CalibrationParameters.
    \warning CalibrationParameters are returned in \ref COORDINATE_SYSTEM "sl::COORDINATE_SYSTEM::IMAGE", they are not impacted by the \ref InitParameters "sl::InitParameters::coordinate_system".
     */
    struct /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ CalibrationParameters {
        /**
        \brief Intrinsics sl::CameraParameters of the left camera.
         */
        CameraParameters left_cam;

        /**
        \brief Intrinsics sl::CameraParameters of the right camera.
         */
        CameraParameters right_cam;

        /**
        \brief Left to right camera transform, expressed in user coordinate system and unit (defined by InitParameters).
         */
        Transform stereo_transform;

        /**
        \brief Return the baseline of the camera in the sl::UNIT defined in sl::InitParameters.coordinate_units.
         */
        float getCameraBaseline();

        /**
         * @brief computes and returns the calibration associated to the query resolution
         * 
         * @param output_resolution the query resolution
         * @return CalibrationParameters
         */
        CalibrationParameters scale(sl::Resolution const& output_resolution) const {
            CalibrationParameters output_calibration_parameters;
            output_calibration_parameters.left_cam = left_cam.scale(output_resolution);
            output_calibration_parameters.right_cam = right_cam.scale(output_resolution);
            output_calibration_parameters.stereo_transform = stereo_transform;
            return output_calibration_parameters;
        }
    };

    /**
    \struct SensorParameters
    \ingroup Sensors_group
    \brief Structure containing information about a single sensor available in the current device.

    Information about the camera sensors is available in the sl::CameraInformation struct returned by sl::Camera.getCameraInformation().
    \note This structure is meant to be used as a read-only container.
    \note Editing any of its fields will not impact the ZED SDK.
     */
    struct SensorParameters {
        sl::SENSOR_TYPE type; /**< \brief Type of the sensor.*/
        float resolution; /**< \brief Resolution of the sensor. */
        float sampling_rate; /**< \brief Sampling rate (or ODR) of the sensor. */
        sl::float2 range; /**< \brief Range of the sensor (minimum: `range.x`, maximum: `range.y`).*/
        float noise_density; /**< \brief White noise density given as continuous (frequency-independent).\note The units will be expressed in `sensor_unit / √(Hz)`.\note `NAN` if the information is not available. */
        float random_walk; /**< \brief Random walk derived from the Allan Variance given as continuous (frequency-independent).\note The units will be expressed in `sensor_unit / √(Hz)`.\note `NAN` if the information is not available. */
        sl::SENSORS_UNIT sensor_unit; /**< \brief Unit of the sensor. */
        bool isAvailable; /**< \brief Whether the sensor is available in your camera.*/
    }; ///@}

    /**
    \struct SensorsConfiguration
    \ingroup Sensors_group
    \brief Structure containing information about all the sensors available in the current device.

    Information about the camera sensors is available in the sl::CameraInformation struct returned by sl::Camera.getCameraInformation().
    \note This structure is meant to be used as a read-only container.
    \note Editing any of its fields will not impact the ZED SDK.
     */
    struct /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ SensorsConfiguration {
        unsigned int firmware_version = 0; /**< \brief Firmware version of the sensor module.\note 0 if no sensors are available ([sl::MODEL::ZED](\ref MODEL)). */
        sl::Transform camera_imu_transform; /**< \brief IMU to left camera transform matrix. \note It contains the rotation and translation between the IMU frame and camera frame. */
        sl::Transform imu_magnetometer_transform; /**< \brief Magnetometer to IMU transform matrix.\note It contains rotation and translation between IMU frame and magnetometer frame. */
        sl::SensorParameters accelerometer_parameters; /**< \brief Configuration of the accelerometer. */
        sl::SensorParameters gyroscope_parameters; /**< \brief Configuration of the gyroscope. */
        sl::SensorParameters magnetometer_parameters; /**< \brief Configuration of the magnetometer. */
        sl::SensorParameters barometer_parameters; /**< \brief Configuration of the barometer. */

        /**
        \brief Checks if a sensor is available on the device.
        \param sensor_type : Sensor type to check.
        \return true if the sensor is available on the device, otherwise false.
         */
        bool isSensorAvailable(const sl::SENSOR_TYPE &sensor_type);
    }; ///@}

    /**
    \struct CameraConfiguration
    \ingroup Core_group
    \brief Structure containing information about the camera sensor.

    Information about the camera is available in the sl::CameraInformation struct returned by sl::Camera::getCameraInformation().

    \note This object is meant to be used as a read-only container, editing any of its field won't impact the ZED SDK.
    \warning sl::CalibrationParameters are returned in sl::COORDINATE_SYSTEM::IMAGE, they are not impacted by the sl::InitParameters.coordinate_system.
     */
    struct CameraConfiguration {
        /**
        \brief Intrinsics and extrinsic stereo parameters for rectified/undistorted images.
         */
        CalibrationParameters calibration_parameters;
        /**
        \brief Intrinsics and extrinsic stereo parameters for unrectified/distorted images.
         */
        CalibrationParameters calibration_parameters_raw;
        /**
        \brief Internal firmware version of the camera.
         */
        unsigned int firmware_version = 0;
        /**
        \brief FPS of the camera.
         */
        float fps = 0;
        /**
        \brief Resolution of the camera.
         */
        Resolution resolution;
    }; ///@}

    /**
    \struct CameraInformation
    \ingroup Core_group
    \brief Structure containing information of a single camera (serial number, model, input type, etc.).

    Information about the camera will be returned by sl::Camera::getCameraInformation().

    \note This object is meant to be used as a read-only container, editing any of its field won't impact the ZED SDK.
     */
    struct CameraInformation {
        /**
        \brief Serial number of the camera.
         */
        unsigned int serial_number = 0;
        /**
        \brief Model of the camera (see sl::MODEL).
         */
        sl::MODEL camera_model = sl::MODEL::LAST;
        /**
        \brief Input type used in the ZED SDK.
         */
        sl::INPUT_TYPE input_type = sl::INPUT_TYPE::LAST;
        /**
        \brief Camera configuration parameters stored in a sl::CameraConfiguration.
         */
        CameraConfiguration camera_configuration;
        /**
        \brief Sensors configuration parameters stored in a sl::SensorsConfiguration.
         */
        SensorsConfiguration sensors_configuration;
    }; ///@}

    /**
    \class Pose
    \ingroup PositionalTracking_group
    \brief Class containing positional tracking data giving the position and orientation of the camera in 3D space.

    Different representations of position and orientation can be retrieved, along with timestamp and pose confidence.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Pose {
        friend class CameraMemberHandler;
        friend class Camera;
        //ZED_SDK_VERSION_ATTRIBUTE
    public:
        /**
        \brief Default constructor.
        
        Creates an empty sl::Pose (identity).
         */
        Pose();

        /**
        \brief Copy constructor (deep copy).
         */
        Pose(const Pose &pose);

        /**
        \brief Constructor.
        
        Initializes the transform of the sl::Pose with a sl::Transform (deep copy).
         */
        Pose(const Transform &pose_data, unsigned long long timestamp = 0, int confidence = 0);

        /**
        \brief Default destructor.
         */
        ~Pose();

        /**
        \brief Returns the sl::Translation corresponding to the current sl::Pose.
        \return sl::Translation created from the sl::Pose values.
         */
        Translation getTranslation();

        /**
        \brief Returns the sl::Orientation corresponding to the current sl::Pose.
        \return sl::Orientation created from the sl::Pose values.
         */
        Orientation getOrientation();

        /**
        \brief Returns the sl::Rotation corresponding to the current sl::Pose.
        \return sl::Rotation created from the sl::Pose values.
         */
        Rotation getRotationMatrix();

        /**
        \brief Returns the 3x1 rotation vector (obtained from 3x3 rotation matrix using Rodrigues formula) corresponding to the current sl::Pose.
        \return Rotation vector created from the sl::Pose values.
         */
        float3 getRotationVector();

        /**
        \brief Converts the rotation component of the sl::Pose into Euler angles.
        \param radian : Whether the angle will be returned in radian or degree.
        \return Euler angles created from the sl::Pose values as a sl::float3 representing the rotations around the X, Y and Z axes using YZX convention.
         */
        float3 getEulerAngles(bool radian = true);

        /**
        \brief sl::Transform containing the rotation and translation data of the sl::Pose.
         */
        Transform pose_data;

        /**
        \brief sl::Timestamp of the sl::Pose.

        This timestamp should be compared with the camera timestamp for synchronization.
         */
        sl::Timestamp timestamp;

        /**
        \brief Confidence/quality of the pose estimation for the target frame.

        A confidence metric of the tracking [0-100] with:
        - 0: tracking is lost
        - 100: tracking can be fully trusted
         */
        int pose_confidence;

        /**
        \brief 6x6 pose covariance matrix of translation (the first 3 values) and rotation in so3 (the last 3 values).
         */
        float pose_covariance[36];

        /**
        \brief Whether the tracking is activated or not.
        \note You should check that first if something is wrong.
         */
        bool valid;

        /**
        \brief Twist of the camera available in reference camera.

        This expresses velocity in free space, broken into its linear and angular parts.
         */
        float twist[6];

        /**
        \brief Row-major representation of the 6x6 twist covariance matrix of the camera.

        This expresses the uncertainty of the twist.
         */
        float twist_covariance[36];
    };

    /**
    \ingroup Sensors_group
    \brief Structure containing all sensors data (except image sensors) to be used for positional tracking or environment study.

    \note Some data are not available in SVO and streaming input mode.
    \note They are specified by a note "Not available in SVO or STREAM mode." in the documentation of a specific data.
    \note If nothing is mentioned in the documentation, they are available in all input modes.
     */
    struct /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ SensorsData {

        /**
        \enum CAMERA_MOTION_STATE
        \ingroup Sensors_group
        \brief Lists different states of the camera motion.
         */
        enum class CAMERA_MOTION_STATE {
            STATIC, /**< The camera is static. */
            MOVING, /**< The camera is moving. */
            FALLING, /**< The camera is falling. */
            ///@cond SHOWHIDDEN
            LAST
            ///@endcond
        };

        /**
        \ingroup Sensors_group
        \brief Structure containing data from the barometer sensor.
         */
        struct /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ BarometerData {
            /**
            \brief Whether the barometer sensor is available in your camera.
             */
            bool is_available;

            /**
            \brief Data acquisition timestamp.
             */
            sl::Timestamp timestamp;

            /**
            \brief Ambient air pressure in hectopascal (hPa).
             */
            float pressure;

            /**
            \brief Relative altitude from first camera position (at sl::Camera.open() time).
             */
            float relative_altitude;

            /**
            \brief Realtime data acquisition rate in hertz (Hz).
             */
            float effective_rate;
        };

        /**
        \ingroup Sensors_group
        \brief Structure containing data from the temperature sensors.
         */
        struct /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ TemperatureData {

            /**
            \enum SENSOR_LOCATION
            \brief Lists possible locations of temperature sensors.
             */
            enum class SENSOR_LOCATION {
                IMU, /**< The temperature sensor is in the IMU. */
                BAROMETER, /**< The temperature sensor is in the barometer. */
                ONBOARD_LEFT, /**< The temperature sensor is next to the left image sensor. */
                ONBOARD_RIGHT, /**< The temperature sensor is next to the right image sensor. */
                ///@cond SHOWHIDDEN
                LAST
                ///@endcond
            };

            /**
            \brief Gets the temperature value at a temperature sensor location.
            \param location : Location of the temperature sensor to request.
            \return Temperature in °C at the requested location.
             */
            ERROR_CODE get(SENSOR_LOCATION location, float &temperature);

            /**
            \brief Map storing the temperatures at the different temperature sensors location.
             */
            std::map<SENSOR_LOCATION, float> temperature_map;
        };

        /**
        \ingroup Sensors_group
        \brief Structure containing data from the magnetometer sensor.
         */
        struct /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ MagnetometerData {

            /**
            \enum HEADING_STATE
            \brief Lists the different states of the magnetic heading.
             */
            enum class HEADING_STATE {
                GOOD, /**< The heading is reliable and not affected by iron interferences. */
                OK, /**< The heading is reliable, but affected by slight iron interferences. */
                NOT_GOOD, /**< The heading is not reliable because affected by strong iron interferences. */
                NOT_CALIBRATED, /**< The magnetometer has not been calibrated. */
                MAG_NOT_AVAILABLE, /**< The magnetometer sensor is not available. */
                ///@cond SHOWHIDDEN
                LAST
                ///@endcond
            };

            /**
            \brief Whether the magnetometer sensor is available in your camera.
             */
            bool is_available;

            /**
            \brief Data acquisition timestamp.
             */
            sl::Timestamp timestamp;

            /**
            \brief Uncalibrated magnetic field local vector in microtesla (μT).
            \note The magnetometer raw values are affected by soft and hard iron interferences.
            \note The sensor must be calibrated by placing the camera in the working environment and using \b ZED \b Sensor \b Viewer tool.
            \note Not available in SVO or STREAM mode.
             */
            sl::float3 magnetic_field_uncalibrated;

            /**
            \brief Magnetic field local vector in microtesla (μT).
            \note To calibrate the magnetometer sensor, please use \b ZED \b Sensor \b Viewer tool after placing the camera in the final operating environment.
             */
            sl::float3 magnetic_field_calibrated;

            /**
            \brief Camera heading in degrees relative to the magnetic North Pole.
            \note The magnetic North Pole has an offset with respect to the geographic North Pole, depending on the geographic position of the camera.
            \note To get a correct magnetic heading, the magnetometer sensor must be calibrated using \b ZED \b Sensor \b Viewer tool.
             */
            float magnetic_heading;

            /**
            \brief State of \ref magnetic_heading.
             */
            HEADING_STATE magnetic_heading_state;

            /**
            \brief Accuracy of \ref magnetic_heading measure in the range [0.0, 1.0].
            \note A negative value means that the magnetometer must be calibrated using \b ZED \b Sensor \b Viewer tool.
             */
            float magnetic_heading_accuracy;

            /**
            \brief Realtime data acquisition rate in hertz (Hz).
             */
            float effective_rate;
        };

        /**
        \ingroup Sensors_group
        \brief Structure containing data from the IMU sensor.
         */
        struct /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ IMUData {
            /**
            \brief Whether the IMU sensor is available in your camera.
             */
            bool is_available;

            /**
            \brief Data acquisition timestamp.
             */

            sl::Timestamp timestamp;

            /**
            \brief IMU pose (IMU 6-DoF fusion).
             */
            sl::Transform pose;

            /**
            \brief Covariance matrix of the IMU pose (\ref pose).
             */
            sl::Matrix3f pose_covariance;

            /**
            \brief Angular velocity vector of the gyroscope in deg/s.

            The value is corrected from bias, scale and misalignment.
            \note The value can be directly ingested in an IMU fusion algorithm to extract a quaternion.
            \note Not available in SVO or STREAM mode.
             */
            sl::float3 angular_velocity;

            /**
            \brief Linear acceleration vector of the gyroscope in m/s².

            The value is corrected from bias, scale and misalignment.
            \note The value can be directly ingested in an IMU fusion algorithm to extract a quaternion.
            \note Not available in SVO or STREAM mode.
             */
            sl::float3 linear_acceleration;

            /**
            \brief Angular velocity vector of the gyroscope in deg/s (uncorrected from the IMU calibration).
            \note The value is the exact raw values from the IMU.
            \note Not available in SVO or STREAM mode.
             */
            sl::float3 angular_velocity_uncalibrated;

            /**
            \brief Linear acceleration vector of the gyroscope in m/s² (uncorrected from the IMU calibration).
            \note The value is the exact raw values from the IMU.
            \note Not available in SVO or STREAM mode.
             */
            sl::float3 linear_acceleration_uncalibrated;

            /**
            \brief Covariance matrix of the angular velocity of the gyroscope in deg/s (\ref angular_velocity).
            \note Not available in SVO or STREAM mode.
             */
            sl::Matrix3f angular_velocity_covariance;

            /**
            \brief Covariance matrix of the linear acceleration of the gyroscope in m/s² (\ref linear_acceleration).
            \note Not available in SVO or STREAM mode.
             */
            sl::Matrix3f linear_acceleration_covariance;

            /**
            \brief Realtime data acquisition rate in hertz (Hz).
             */
            float effective_rate;
        };

        /**
        \brief Default constructor.

        Creates an empty sl::SensorsData (identity).
         */
        SensorsData();

        /**
        \brief Copy constructor (deep copy).
         */
        SensorsData(const SensorsData &data);

        /**
        \brief Barometer data.
         */
        BarometerData barometer;

        /**
        \brief Temperature data.
         */
        TemperatureData temperature;

        /**
        \brief Magnetometer data.
         */
        MagnetometerData magnetometer;

        /**
        \brief IMU data.
         */
        IMUData imu;

        ////////////////// Detection //////////////////////
        /**
        \brief Motion state of the camera.
         */
        CAMERA_MOTION_STATE camera_moving_state;

        ////////////////// Sync //////////////////////

        /**
        \brief Indicates if the sensors data has been taken during a frame capture on sensor.

        If the value is 1, the data has been taken during the same time than a frame has been acquired by the left sensor (the time precision is linked to the IMU rate, therefore 800Hz == 1.3ms).
        \n If the value is 0, the data has not been taken during a frame acquisition.
         */
        int image_sync_trigger;
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const sl::SensorsData::MagnetometerData::HEADING_STATE &mag_heading_state);

    inline std::ostream &operator<<(std::ostream &os, const sl::SensorsData::MagnetometerData::HEADING_STATE &mag_heading_state) {
        return os << toString(mag_heading_state);
    }

    String SL_CORE_EXPORT toString(const sl::SensorsData::CAMERA_MOTION_STATE &camera_moving_state);

    inline std::ostream &operator<<(std::ostream &os, const sl::SensorsData::CAMERA_MOTION_STATE &camera_moving_state) {
        return os << toString(camera_moving_state);
    }

    String SL_CORE_EXPORT toString(const sl::SensorsData::TemperatureData::SENSOR_LOCATION &sensor_loc);

    inline std::ostream &operator<<(std::ostream &os, const sl::SensorsData::TemperatureData::SENSOR_LOCATION &sensor_loc) {
        return os << toString(sensor_loc);
    }
    ///@endcond

    /*!
    \brief Compute the rotation matrix from the gravity vector : the rotation can used to find the world rotation from the gravity of an IMU
    \param axis_to_align : define the axis to align with the gravity, for instance : to align the "y" axis, axis_to_align = (0, 1, 0)'
    \param gravity_vector : the gravity vector, acceleration set by an IMU
    \return Rotation : rotation matrix, useful for Camera::detectFloorPlane as a gravity prior
     */
    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Rotation computeRotationMatrixFromGravity(sl::float3 axis_to_align, sl::float3 gravity_vector);

    /*!
    \brief Get the coordinate transform conversion matrix to change coordinate system.
    \param coord_system_src : the source coordinate system.
    \param coord_system_dst : the destination coordinate system.
    \return Matrix3f : transformation matrix, to apply to a \ref float3 point simply multiply by this matrix (pt_coord_dst = tf_matrix * pt_coord_src).
     */
    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Matrix3f getCoordinateTransformConversion3f(COORDINATE_SYSTEM coord_system_src, COORDINATE_SYSTEM coord_system_dst);

    /*!
    \brief Get the coordinate transform conversion matrix to change coordinate system.
    \param coord_system_src : the source coordinate system.
    \param coord_system_dst : the destination coordinate system.
    \return Matrix4f : transformation matrix, to apply to a \ref float4 point simply multiply by this matrix (pt_coord_dst = tf_matrix * pt_coord_src).
     */
    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Matrix4f getCoordinateTransformConversion4f(COORDINATE_SYSTEM coord_system_src, COORDINATE_SYSTEM coord_system_dst);

    /*!
    \brief Change the coordinate system of a matrix.
    \param floatMat : (in/out) matrix to transform, can be either a \ref MAT_TYPE::F32_C4 (the fourth value will be ignored as it contained the color information) or a \ref MAT_TYPE::F32_C3.
    \param coord_system_src : the current coordinate system of floatMat.
    \param coord_system_dst : the destination coordinate system for floatMat.
    \param mem : define which memory should be transformed from floatMat.
    \return \ref SUCCESS if everything went well, \ref ERROR_CODE::FAILURE otherwise.
     */
    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ ERROR_CODE convertCoordinateSystem(Mat &floatMat, COORDINATE_SYSTEM coord_system_src, COORDINATE_SYSTEM coord_system_dst, MEM mem = MEM::CPU);

    /*!
    \brief Change the coordinate system of a transform matrix.
    \param motionMat : (in/out) matrix to transform
    \param coord_system_src : the current coordinate system of motionMat.
    \param coord_system_dst : the destination coordinate system for motionMat.
    \return \ref SUCCESS if everything went well, \ref ERROR_CODE::FAILURE otherwise.
     */
    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ ERROR_CODE convertCoordinateSystem(Transform &motionMat, COORDINATE_SYSTEM coord_system_src, COORDINATE_SYSTEM coord_system_dst);

    /*!
    \brief Get the unit factor to change units.
    \param unit_src : the source coordinate system.
    \param unit_dst : the destination coordinate system.
    \return float : unit scale (pt_coord_dst = factor * pt_coord_src).
     */
    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ float getUnitScale(UNIT unit_src, UNIT unit_dst);

    /*!
    \brief Change the unit of a matrix.
    \param floatMat : (in/out) matrix to transform, can be either a \ref MAT_TYPE::F32_C4 (the fourth value will be ignored as it contained the color information), \ref MAT_TYPE::F32_C3 or a \ref MAT_TYPE::F32_C1.
    \param unit_src : the current unit of floatMat.
    \param unit_dst : the destination unit for floatMat.
    \param mem : define which memory should be transformed from floatMat.
    \return \ref SUCCESS if everything went well, \ref ERROR_CODE::FAILURE otherwise.
     */
    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ ERROR_CODE convertUnit(Mat &floatMat, UNIT unit_src, UNIT unit_dst, MEM mem = MEM::CPU);

    /*!
    \brief Change the unit (of the translations) of a transform matrix.
    \param motionMat : (in/out) matrix to transform
    \param unit_src : the current unit of motionMat.
    \param unit_dst : the destination unit for motionMat.
    \return \ref SUCCESS if everything went well, \ref ERROR_CODE::FAILURE otherwise.
     */
    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ ERROR_CODE convertUnit(Transform &motionMat, UNIT unit_src, UNIT unit_dst);

    /**
    \enum MODULE
    \ingroup Core_group
    \brief Lists available modules.
     */
    enum class MODULE {
        ALL = 0, /**< All modules*/
        DEPTH = 1,
        POSITIONAL_TRACKING = 2,
        OBJECT_DETECTION = 3,
        BODY_TRACKING = 4,
        SPATIAL_MAPPING = 5,
        LAST = 6
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const MODULE &mod);

    inline std::ostream &operator<<(std::ostream &os, const MODULE &mod) {
        return os << toString(mod);
    }
    /*@endcond*/

    /**
    \enum OBJECT_CLASS
    \ingroup Object_group
    \brief Lists available object classes.
     */
    enum class OBJECT_CLASS {
        PERSON = 0, /**< For people detection */
        VEHICLE = 1, /**< For vehicle detection (cars, trucks, buses, motorcycles, etc.) */
        BAG = 2, /**< For bag detection (backpack, handbag, suitcase, etc.) */
        ANIMAL = 3, /**< For animal detection (cow, sheep, horse, dog, cat, bird, etc.) */
        ELECTRONICS = 4, /**< For electronic device detection (cellphone, laptop, etc.) */
        FRUIT_VEGETABLE = 5, /**< For fruit and vegetable detection (banana, apple, orange, carrot, etc.) */
        SPORT = 6, /**< For sport-related object detection (sport ball, etc.) */
        ///@cond SHOWHIDDEN
        LAST = 7
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const OBJECT_CLASS &object_class);

    inline std::ostream &operator<<(std::ostream &os, const OBJECT_CLASS &object_class) {
        return os << toString(object_class);
    }
    ///@endcond

    /**
    \enum OBJECT_SUBCLASS
    \ingroup Object_group
    \brief List available object subclasses.

    Given as hint, when using object tracking an object can change of sl::OBJECT_SUBCLASS while keeping the same sl::OBJECT_CLASS
    (i.e.: frame n: MOTORBIKE, frame n+1: BICYCLE).
     */
    enum class OBJECT_SUBCLASS {
        PERSON = 0, /**< PERSON */
        PERSON_HEAD = 22, /**< PERSON */
        BICYCLE = 1, /**< VEHICLE */
        CAR = 2, /**< VEHICLE */
        MOTORBIKE = 3, /**< VEHICLE */
        BUS = 4, /**< VEHICLE */
        TRUCK = 5, /**< VEHICLE */
        BOAT = 6, /**< VEHICLE */
        BACKPACK = 7, /**< BAG */
        HANDBAG = 8, /**< BAG */
        SUITCASE = 9, /**< BAG */
        BIRD = 10, /**< ANIMAL */
        CAT = 11, /**< ANIMAL */
        DOG = 12, /**< ANIMAL */
        HORSE = 13, /**< ANIMAL */
        SHEEP = 14, /**< ANIMAL */
        COW = 15, /**< ANIMAL */
        CELLPHONE = 16, /**< ELECTRONICS */
        LAPTOP = 17, /**< ELECTRONICS */
        BANANA = 18, /**< FRUIT_VEGETABLE */
        APPLE = 19, /**< FRUIT_VEGETABLE */
        ORANGE = 20, /**< FRUIT_VEGETABLE */
        CARROT = 21, /**< FRUIT_VEGETABLE */
        SPORTSBALL = 23, /**< SPORT */
        ///@cond SHOWHIDDEN
        LAST = 24
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const OBJECT_SUBCLASS &object_subclass);

    inline std::ostream &operator<<(std::ostream &os, const OBJECT_SUBCLASS &object_subclass) {
        return os << toString(object_subclass);
    }
    ///@endcond

    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ OBJECT_CLASS getObjectClass(OBJECT_SUBCLASS object_type);
    /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ std::vector<OBJECT_SUBCLASS> getObjectSubClasses(OBJECT_CLASS object_type);

    /**
    \enum OBJECT_TRACKING_STATE
    \ingroup Object_group
    \brief Lists the different states of object tracking.
     */
    enum class OBJECT_TRACKING_STATE {
        OFF, /**< The tracking is not yet initialized.\n The object id is not usable. */
        OK, /**< The object is tracked. */
        SEARCHING, /**< The object could not be detected in the image and is potentially occluded.\n The trajectory is estimated. */
        TERMINATE, /**< This is the last searching state of the track.\n The track will be deleted in the next sl::Camera.retrieveObjects(). */
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const OBJECT_TRACKING_STATE &object_track_state);

    inline std::ostream &operator<<(std::ostream &os, const OBJECT_TRACKING_STATE &object_track_state) {
        return os << toString(object_track_state);
    }
    ///@endcond

    /**
    \enum OBJECT_ACTION_STATE
    \ingroup Object_group
    \brief Lists the different states of an object's actions.
     */
    enum class OBJECT_ACTION_STATE {
        IDLE = 0, /**< The object is staying static. */
        MOVING = 1, /**< The object is moving. */
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const OBJECT_ACTION_STATE &object_action_state);

    inline std::ostream &operator<<(std::ostream &os, const OBJECT_ACTION_STATE &object_action_state) {
        return os << toString(object_action_state);
    }
    ///@endcond

    /**
    \enum OBJECT_FILTERING_MODE
    \ingroup Object_group
    \brief Lists supported bounding box preprocessing.
     */
    enum class OBJECT_FILTERING_MODE {
        NONE, /**< The ZED SDK will not apply any preprocessing to the detected objects. */
        NMS3D, /**< The ZED SDK will remove objects that are in the same 3D position as an already tracked object (independent of class id). */
        NMS3D_PER_CLASS, /**< The ZED SDK will remove objects that are in the same 3D position as an already tracked object of the same class id. */
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const OBJECT_FILTERING_MODE &object_filtering_mode);

    inline std::ostream &operator<<(std::ostream &os, const OBJECT_FILTERING_MODE &object_filtering_mode) {
        return os << toString(object_filtering_mode);
    }
    ///@endcond

    /**
     * \ingroup Body_group
     * \brief Report the actual inference precision used
     */
    enum class INFERENCE_PRECISION {
        FP32 = 0,
        FP16 = 1,
        INT8 = 2,
        ///@cond SHOWHIDDEN
        LAST = 3
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const sl::INFERENCE_PRECISION &precision);

    inline std::ostream &operator<<(std::ostream &os, const sl::INFERENCE_PRECISION &precision) {
        return os << toString(precision);
    }
    ///@endcond

    /**
    \enum BODY_FORMAT
    \ingroup Body_group
    \brief Lists supported skeleton body models.
     */
    enum class BODY_FORMAT {
        /**
         * \brief 18-keypoint model
         * \n Basic body model
         */
        BODY_18,

        /**
         * \brief 34-keypoint model
         * \note Requires body fitting enabled.
         */
        BODY_34,

        /**
         * \brief 38-keypoint model
         * \n Including simplified face, hands and feet.
         * \note Early Access
         */
        BODY_38,

        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const BODY_FORMAT &body_format);

    inline std::ostream &operator<<(std::ostream &os, const BODY_FORMAT &body_format) {
        return os << toString(body_format);
    }
    ///@endcond

    /**
    \enum BODY_KEYPOINTS_SELECTION
    \ingroup Body_group
    \brief Lists supported models for skeleton keypoints selection.
     */
    enum class BODY_KEYPOINTS_SELECTION {
        /**
         * \brief Full keypoint model
         */
        FULL,

        /**
         * \brief Upper body keypoint model
         * \n Will output only upper body (from hip).
         */
        UPPER_BODY,

        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const BODY_KEYPOINTS_SELECTION &body_selection);

    inline std::ostream &operator<<(std::ostream &os, const BODY_KEYPOINTS_SELECTION &body_selection) {
        return os << toString(body_selection);
    }
    ///@endcond

    /**
    \enum REFERENCE_FRAME
    \ingroup PositionalTracking_group
    \brief Lists possible types of position matrix used to store camera path and pose.
     */
    enum class REFERENCE_FRAME {
        WORLD, /**< The transform of sl::Pose will contain the motion with reference to the world frame (previously called PATH).*/
        CAMERA, /**< The transform of sl::Pose will contain the motion with reference to the previous camera frame (previously called POSE).*/
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const REFERENCE_FRAME &ref_frame);

    inline ::std::ostream &operator<<(::std::ostream &os, const REFERENCE_FRAME &ref_frame) {
        return os << toString(ref_frame);
    }
    ///@endcond

    /**
    \ingroup Object_group
    \brief Class containing data of a detected object such as its \ref bounding_box, \ref label, \ref id and its 3D \ref position.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ ObjectData {
        friend class CameraMemberHandler;

    public:
        /**
        \brief Default constructor.
         */
        ObjectData();
        /**
        \brief Default destructor.
         */
        ~ObjectData();

        /**
        \brief Object identification number.

        It is used as a reference when tracking the object through the frames.
        \note Only available if sl::ObjectDetectionParameters.enable_tracking is activated.
        \note Otherwise, it will be set to -1.
         */
        int id;

        /**
        \brief Unique id to help identify and track AI detections.

        It can be either generated externally, or by using \ref generate_unique_id() or left empty.
         */
        String unique_object_id;

        /**
        \brief Object raw label.

        It is forwarded from sl::CustomBoxObjectData when using [sl::OBJECT_DETECTION_MODEL::CUSTOM_BOX_OBJECTS](\ref OBJECT_DETECTION_MODEL).
         */
        int raw_label = 0;

        /**
        \brief Object class/category to identify the object type.
         */
        OBJECT_CLASS label;

        /**
        \brief Object sub-class/sub-category to identify the object type.
         */
        OBJECT_SUBCLASS sublabel;

        /**
        \brief Object tracking state.
         */
        OBJECT_TRACKING_STATE tracking_state;

        /**
        \brief Object action state.
         */
        OBJECT_ACTION_STATE action_state;

        /**
        \brief Object 3D centroid.
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        sl::float3 position;

        /**
        \brief Object 3D velocity.
        \note It is defined in ```sl::InitParameters.coordinate_units / s``` and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        sl::float3 velocity;

        /**
        \brief Covariance matrix of the 3D position.
        \note It is represented by its upper triangular matrix value
        \code
             = [p0, p1, p2]
               [p1, p3, p4]
               [p2, p4, p5]
        \endcode
        where pi is ```position_covariance[i]```
         */
        float position_covariance[6];

        /**
        \brief 2D bounding box of the object represented as four 2D points starting at the top left corner and rotation clockwise.
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
        \code
        A ------ B
        | Object |
        D ------ C
        \endcode
         */
        std::vector<sl::uint2> bounding_box_2d;

        /**
        \brief Mask defining which pixels which belong to the object (in \ref bounding_box_2d and set to 255) and those of the background (set to 0).
        \warning The mask information is only available for tracked objects ([sl::OBJECT_TRACKING_STATE::OK](\ref OBJECT_TRACKING_STATE)) that have a valid depth.
        \warning Otherwise, the mask will not be initialized (```mask.isInit() == false```).
         */
        sl::Mat mask;

        /**
        \brief Detection confidence value of the object.

        From 0 to 100, a low value means the object might not be localized perfectly or the label (sl::OBJECT_CLASS) is uncertain.
         */
        float confidence;

        /**
        \brief 3D bounding box of the object represented as eight 3D points.
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
        \code
           1 ------ 2
          /        /|
         0 ------ 3 |
         | Object | 6
         |        |/
         4 ------ 7
        \endcode
         */
        std::vector<sl::float3> bounding_box;

        /**
        \brief 3D object dimensions: width, height, length.
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        sl::float3 dimensions;

        /**
        \brief 2D bounding box of the head of the object (a person) represented as four 2D points starting at the top left corner and rotation clockwise.
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
        \warning Not available with [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_XXX](\ref OBJECT_DETECTION_MODEL).
         */
        std::vector<sl::uint2> head_bounding_box_2d;

        /**
        \brief 3D bounding box of the head of the object (a person) represented as eight 3D points.
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
        \warning Not available with [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_XXX](\ref OBJECT_DETECTION_MODEL).
         */
        std::vector<sl::float3> head_bounding_box;

        /**        
        \brief 3D centroid of the head of the object (a person).
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
        \warning Not available with [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_XXX](\ref OBJECT_DETECTION_MODEL).
         */
        sl::float3 head_position;
    };

    /**
    \ingroup Object_group
    \brief Generate a UUID like unique id to help identify and track AI detections.
     */
    String /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ generate_unique_id();

    /**
    \ingroup Object_group
    \brief Class that store externally detected objects.

    The objects can be ingested with sl::Camera.ingestCustomBoxObjects() to extract 3D and tracking information over time.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ CustomBoxObjectData {
    public:

        /**
        \brief Default constructor.
         */
        CustomBoxObjectData();

        /**
        \brief Unique id to help identify and track AI detections.

        It can be either generated externally, or by using \ref generate_unique_id() or left empty.
         */
        String unique_object_id;

        /**
        \brief 2D bounding box of the object represented as four 2D points starting at the top left corner and rotation clockwise.
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
        \code
        A ------ B
        | Object |
        D ------ C
        \endcode
         */
        std::vector<sl::uint2> bounding_box_2d;

        /**
        \brief Object label.

        This information is passed-through and can be used to improve object tracking.
        \note It should define an object class. This means that any similar object (in classification) should share the same label number.
         */
        int label;

        /**
        \brief Detection confidence value of the object.
        \note The value should be in ```[0-1]```.
        \note It can be used to improve the object tracking.
         */
        float probability;

        /**
        \brief Provide hypothesis about the object movements (degrees of freedom or DoF) to improve the object tracking.
        - true: 2 DoF projected alongside the floor plane. Case for object standing on the ground such as person, vehicle, etc. 
        \n The projection implies that the objects cannot be superposed on multiple horizontal levels. 
        - false: 6 DoF (full 3D movements are allowed).

        \note This parameter cannot be changed for a given object tracking id.
        \note It is advised to set it by labels to avoid issues.
         */
        bool is_grounded = true;
    };

    /**
    \ingroup Object_group
    \brief Class containing the results of the object detection module.

    The detected objects are listed in \ref object_list.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Objects {
    public:
        /**
        \brief Timestamp corresponding to the frame acquisition. 

        This value is especially useful for the async mode to synchronize the data.
         */
        sl::Timestamp timestamp;

        /**
        \brief Vector of detected objects.
         */
        std::vector<sl::ObjectData> object_list;

        /**
        \brief Whether \ref object_list has already been retrieved or not.
         */
        bool is_new = false;

        /**
        \brief Whether both the object tracking and the world orientation has been setup.
         */
        bool is_tracked = false;

        /**
        \brief Method that looks for a given object id in the current objects list.
        \param objectData[out] : sl::ObjectData to fill if the search succeeded.
        \param objectDataId[in] : Id of the sl::ObjectData to search.
        \return True if found, otherwise false.
         */
        bool getObjectDataFromId(sl::ObjectData &objectData, int objectDataId);

    };

    /**
   \ingroup Body_group
   \brief Class containing data of a detected body/person such as its \ref bounding_box, \ref id and its 3D \ref position.

     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ BodyData {
        friend class CameraMemberHandler;

    public:
        /**
        \brief Default constructor.
         */
        BodyData();
        /**
        \brief Default destructor.
         */
        ~BodyData();

        /**
        \brief Body/person identification number.

        It is used as a reference when tracking the body through the frames.
        \note Only available if sl::BodyTrackingParameters.enable_tracking is activated.
        \note Otherwise, it will be set to -1.
         */
        int id;

        /**
        \brief Unique id to help identify and track AI detections.

        It can be either generated externally, or by using \ref generate_unique_id() or left empty.
         */
        String unique_object_id;

        /**
        \brief Body/person tracking state.
         */
        OBJECT_TRACKING_STATE tracking_state;

        /**
        \brief Body/person action state.
         */
        OBJECT_ACTION_STATE action_state;

        /**
        \brief Body/person 3D centroid.
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        sl::float3 position;

        /**
        \brief Body/person 3D velocity.
        \note It is defined in ```sl::InitParameters.coordinate_units / s``` and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        sl::float3 velocity;

        /**
        \brief Covariance matrix of the 3D position.
        \note It is represented by its upper triangular matrix value
        \code
             = [p0, p1, p2]
               [p1, p3, p4]
               [p2, p4, p5]
        \endcode
        where pi is ```position_covariance[i]```
         */
        float position_covariance[6];

        /**
        \brief 2D bounding box of the body/person represented as four 2D points starting at the top left corner and rotation clockwise.
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
        \code
        A ------ B
        | Object |
        D ------ C
        \endcode
         */
        std::vector<sl::uint2> bounding_box_2d;

        /**
        \brief Mask defining which pixels which belong to the body/person (in \ref bounding_box_2d and set to 255) and those of the background (set to 0).
        \warning The mask information is only available for tracked bodies ([sl::OBJECT_TRACKING_STATE::OK](\ref OBJECT_TRACKING_STATE)) that have a valid depth.
        \warning Otherwise, the mask will not be initialized (```mask.isInit() == false```).
         */
        sl::Mat mask;

        /**
        \brief Detection confidence value of the body/person.

        From 0 to 100, a low value means the body might not be localized perfectly.
         */
        float confidence;

        /**
        \brief 3D bounding box of the body/person represented as eight 3D points.
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
        \code
           1 ------ 2
          /        /|
         0 ------ 3 |
         | Object | 6
         |        |/
         4 ------ 7
        \endcode
         */
        std::vector<sl::float3> bounding_box;

        /**
        \brief 3D body/person dimensions: width, height, length.
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        sl::float3 dimensions;

        /**
        \brief Set of useful points representing the human body in 2D.
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
        \warning In some cases, eg. body partially out of the image, some keypoints can not be detected. They will have negatives coordinates.
         */
        std::vector<sl::float2> keypoint_2d;

        /**
        \brief Set of useful points representing the human body in 3D.
        \note They are defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
        \warning In some cases, eg. body partially out of the image or missing depth data, some keypoints can not be detected. They will have non finite values.
         */
        std::vector<sl::float3> keypoint;

        /**
        \brief 2D bounding box of the head of the body/person represented as four 2D points starting at the top left corner and rotation clockwise.
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
         */
        std::vector<sl::uint2> head_bounding_box_2d;

        /**
        \brief 3D bounding box of the head of the body/person represented as eight 3D points.
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        std::vector<sl::float3> head_bounding_box;

        /**        
        \brief 3D centroid of the head of the body/person.
        \note It is defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        sl::float3 head_position;

        /**
        \brief Vector of detection confidences for each keypoint.
        \note They can not be lower than the sl::BodyTrackingRuntimeParameters.detection_confidence_threshold.
        \warning In some cases, eg. body partially out of the image or missing depth data, some keypoints can not be detected. They will have non finite values.
         */
        std::vector<float> keypoint_confidence;

        /**
        \brief Vector of detection covariance for each keypoint.
        \warning In some cases, eg. body partially out of the image or missing depth data, some keypoints can not be detected. Their covariances will be 0.
         */
        std::vector<std::array<float, 6 >> keypoint_covariances;

        /**
        \brief Vector of local position (position of the child keypoint with respect to its parent expressed in its parent coordinate frame) for each keypoint.
        \note They are expressed in [sl::REFERENCE_FRAME::CAMERA](\ref REFERENCE_FRAME) or [sl::REFERENCE_FRAME::WORLD](\ref REFERENCE_FRAME).
        \warning Not available with [sl::BODY_FORMAT::BODY_18](\ref BODY_FORMAT).
         */
        std::vector<sl::float3> local_position_per_joint;

        /**
        \brief Vector of local orientation for each keypoint.
        \note The orientation is represented by a quaternion stored in a sl::float4 (```sl::float4 q = sl::float4(qx, qy, qz, qw);```)
        \warning Not available with [sl::BODY_FORMAT::BODY_18](\ref BODY_FORMAT).
         */
        std::vector<sl::float4> local_orientation_per_joint;

        /**
        \brief Global root orientation of the skeleton.

        The orientation is also represented by a quaternion with the same format as \ref local_orientation_per_joint.
        \note The global root position is already accessible in \ref keypoint attribute by using the root index of a given sl::BODY_FORMAT.
        \warning Not available with [sl::BODY_FORMAT::BODY_18](\ref BODY_FORMAT).
         */
        sl::float4 global_root_orientation;

    };

    /**
   \ingroup Body_group
   \brief Class containing the results of the body tracking module.

    The detected bodies/persons are listed in \ref body_list.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Bodies {
    public:
        /**
        \brief Timestamp corresponding to the frame acquisition. 

        This value is especially useful for the async mode to synchronize the data.
         */
        sl::Timestamp timestamp;

        /**
        \brief Vector of detected bodies/persons.
         */
        std::vector<sl::BodyData> body_list;

        /**
        \brief Whether \ref body_list has already been retrieved or not.
         */
        bool is_new = false;

        /**
        \brief Whether both the body tracking and the world orientation has been setup.
         */
        bool is_tracked = false;

        /**
        \brief Status of the actual inference precision mode used to detect the bodies/persons.
        \note It depends on the GPU hardware support, the sl::BodyTrackingParameters.allow_reduced_precision_inference input parameter and the model support.
         */
        sl::INFERENCE_PRECISION inference_precision_mode;

        /**
        \brief Body format used in sl::BodyTrackingParameters.body_format parameter.
         */
        BODY_FORMAT body_format;

        /**
        \brief Method that looks for a given body id in the current bodies list.
        \param bodyData[out] : sl::BodyData to fill if the search succeeded.
        \param bodyDataId[in] : Id of the sl::BodyData to search.
        \return True if found, otherwise false.
         */
        bool getBodyDataFromId(sl::BodyData &bodyData, int bodyDataId);
    };

    /**
     * \ingroup Body_group
     * \brief Semantic of human body parts and order of sl::BodyData::keypoint for \ref BODY_FORMAT "sl::BODY_FORMAT::BODY_18".
     */
    enum class BODY_18_PARTS {
        NOSE = 0, /**< 0*/
        NECK = 1, /**< 1*/
        RIGHT_SHOULDER = 2, /**< 2*/
        RIGHT_ELBOW = 3, /**< 3*/
        RIGHT_WRIST = 4, /**< 4*/
        LEFT_SHOULDER = 5, /**< 5*/
        LEFT_ELBOW = 6, /**< 6*/
        LEFT_WRIST = 7, /**< 7*/
        RIGHT_HIP = 8, /**< 8*/
        RIGHT_KNEE = 9, /**< 9*/
        RIGHT_ANKLE = 10, /**< 10*/
        LEFT_HIP = 11, /**< 11*/
        LEFT_KNEE = 12, /**< 12*/
        LEFT_ANKLE = 13, /**< 13*/
        RIGHT_EYE = 14, /**< 14*/
        LEFT_EYE = 15, /**< 15*/
        RIGHT_EAR = 16, /**< 16*/
        LEFT_EAR = 17, /**< 17*/
        ///@cond SHOWHIDDEN
        LAST = 18
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const sl::BODY_18_PARTS &body_part);

    inline std::ostream &operator<<(std::ostream &os, const sl::BODY_18_PARTS &body_part) {
        return os << toString(body_part);
    }
    ///@endcond

    /**
     * \ingroup Body_group
     * \brief Semantic of human body parts and order of sl::BodyData::keypoint for \ref BODY_FORMAT "sl::BODY_FORMAT::BODY_34".
     */
    enum class BODY_34_PARTS {
        PELVIS = 0, /**< 0*/
        NAVAL_SPINE = 1, /**< 1*/
        CHEST_SPINE = 2, /**< 2*/
        NECK = 3, /**< 3*/
        LEFT_CLAVICLE = 4, /**< 4*/
        LEFT_SHOULDER = 5, /**< 5*/
        LEFT_ELBOW = 6, /**< 6*/
        LEFT_WRIST = 7, /**< 7*/
        LEFT_HAND = 8, /**< 8*/
        LEFT_HANDTIP = 9, /**< 9*/
        LEFT_THUMB = 10, /**< 10*/
        RIGHT_CLAVICLE = 11, /**< 11*/
        RIGHT_SHOULDER = 12, /**< 12*/
        RIGHT_ELBOW = 13, /**< 13*/
        RIGHT_WRIST = 14, /**< 14*/
        RIGHT_HAND = 15, /**< 15*/
        RIGHT_HANDTIP = 16, /**< 16*/
        RIGHT_THUMB = 17, /**< 17*/
        LEFT_HIP = 18, /**< 18*/
        LEFT_KNEE = 19, /**< 19*/
        LEFT_ANKLE = 20, /**< 20*/
        LEFT_FOOT = 21, /**< 21*/
        RIGHT_HIP = 22, /**< 22*/
        RIGHT_KNEE = 23, /**< 23*/
        RIGHT_ANKLE = 24, /**< 24*/
        RIGHT_FOOT = 25, /**< 25*/
        HEAD = 26, /**< 26*/
        NOSE = 27, /**< 27*/
        LEFT_EYE = 28, /**< 28*/
        LEFT_EAR = 29, /**< 29*/
        RIGHT_EYE = 30, /**< 30*/
        RIGHT_EAR = 31, /**< 31*/
        LEFT_HEEL = 32, /**< 32*/
        RIGHT_HEEL = 33, /**< 33*/
        ///@cond SHOWHIDDEN
        LAST = 34
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const sl::BODY_34_PARTS &body_part);

    inline std::ostream &operator<<(std::ostream &os, const sl::BODY_34_PARTS &body_part) {
        return os << toString(body_part);
    }
    ///@endcond

    /**
     * \ingroup Body_group
     * \brief Semantic of human body parts and order of sl::BodyData::keypoint for \ref BODY_FORMAT "sl::BODY_FORMAT::BODY_38".
     */
    enum class BODY_38_PARTS {
        PELVIS = 0, /**< 0*/
        SPINE_1 = 1, /**< 1*/
        SPINE_2 = 2, /**< 2*/
        SPINE_3 = 3, /**< 3*/
        NECK = 4, /**< 4*/
        NOSE = 5, /**< 5*/
        LEFT_EYE = 6, /**< 6*/
        RIGHT_EYE = 7, /**< 7*/
        LEFT_EAR = 8, /**< 8*/
        RIGHT_EAR = 9, /**< 9*/
        LEFT_CLAVICLE = 10, /**< 10*/
        RIGHT_CLAVICLE = 11, /**< 11*/
        LEFT_SHOULDER = 12, /**< 12*/
        RIGHT_SHOULDER = 13, /**< 13*/
        LEFT_ELBOW = 14, /**< 14*/
        RIGHT_ELBOW = 15, /**< 15*/
        LEFT_WRIST = 16, /**< 16*/
        RIGHT_WRIST = 17, /**< 17*/
        LEFT_HIP = 18, /**< 18*/
        RIGHT_HIP = 19, /**< 19*/
        LEFT_KNEE = 20, /**< 20*/
        RIGHT_KNEE = 21, /**< 21*/
        LEFT_ANKLE = 22, /**< 22*/
        RIGHT_ANKLE = 23, /**< 23*/
        LEFT_BIG_TOE = 24, /**< 24*/
        RIGHT_BIG_TOE = 25, /**< 25*/
        LEFT_SMALL_TOE = 26, /**< 26*/
        RIGHT_SMALL_TOE = 27, /**< 27*/
        LEFT_HEEL = 28, /**< 28*/
        RIGHT_HEEL = 29, /**< 29*/
        // Hands
        LEFT_HAND_THUMB_4 = 30, /**< 30*/ // tip
        RIGHT_HAND_THUMB_4 = 31, /**< 31*/
        LEFT_HAND_INDEX_1 = 32, /**< 32*/ // knuckle
        RIGHT_HAND_INDEX_1 = 33, /**< 33*/
        LEFT_HAND_MIDDLE_4 = 34, /**< 34*/ // tip
        RIGHT_HAND_MIDDLE_4 = 35, /**< 35*/
        LEFT_HAND_PINKY_1 = 36, /**< 36*/ // knuckle
        RIGHT_HAND_PINKY_1 = 37, /**< 37*/
        ///@cond SHOWHIDDEN
        LAST = 38
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const sl::BODY_38_PARTS &body_part);

    inline std::ostream &operator<<(std::ostream &os, const sl::BODY_38_PARTS &body_part) {
        return os << toString(body_part);
    }
    ///@endcond

    /**
     * \ingroup Body_group
     * \brief Return associated index of each sl::BODY_18_PARTS.
     */
    inline int getIdx(BODY_18_PARTS part) {
        return static_cast<int> (part);
    }

    /**
     * \ingroup Body_group
     * \brief Return associated index of each sl::BODY_34_PARTS.
     */
    inline int getIdx(BODY_34_PARTS part) {
        return static_cast<int> (part);
    }

    /**
     * \ingroup Body_group
     * \brief Return associated index of each sl::BODY_38_PARTS.
     */
    inline int getIdx(BODY_38_PARTS part) {
        return static_cast<int> (part);
    }

    /**
     * \ingroup Body_group
     * \brief Lists links of human body keypoints for \ref BODY_FORMAT "sl::BODY_FORMAT::BODY_18".
     * \n Useful for display.
     */
    const std::vector<std::pair<BODY_18_PARTS, BODY_18_PARTS>> BODY_18_BONES
    {
        {
            BODY_18_PARTS::NOSE, BODY_18_PARTS::NECK
        },
        {
            BODY_18_PARTS::NECK, BODY_18_PARTS::RIGHT_SHOULDER
        },
        {
            BODY_18_PARTS::RIGHT_SHOULDER, BODY_18_PARTS::RIGHT_ELBOW
        },
        {
            BODY_18_PARTS::RIGHT_ELBOW, BODY_18_PARTS::RIGHT_WRIST
        },
        {
            BODY_18_PARTS::NECK, BODY_18_PARTS::LEFT_SHOULDER
        },
        {
            BODY_18_PARTS::LEFT_SHOULDER, BODY_18_PARTS::LEFT_ELBOW
        },
        {
            BODY_18_PARTS::LEFT_ELBOW, BODY_18_PARTS::LEFT_WRIST
        },
        {
            BODY_18_PARTS::RIGHT_SHOULDER, BODY_18_PARTS::RIGHT_HIP
        },
        {
            BODY_18_PARTS::RIGHT_HIP, BODY_18_PARTS::RIGHT_KNEE
        },
        {
            BODY_18_PARTS::RIGHT_KNEE, BODY_18_PARTS::RIGHT_ANKLE
        },
        {
            BODY_18_PARTS::LEFT_SHOULDER, BODY_18_PARTS::LEFT_HIP
        },
        {
            BODY_18_PARTS::LEFT_HIP, BODY_18_PARTS::LEFT_KNEE
        },
        {
            BODY_18_PARTS::LEFT_KNEE, BODY_18_PARTS::LEFT_ANKLE
        },
        {
            BODY_18_PARTS::RIGHT_SHOULDER, BODY_18_PARTS::LEFT_SHOULDER
        },
        {
            BODY_18_PARTS::RIGHT_HIP, BODY_18_PARTS::LEFT_HIP
        },
        {
            BODY_18_PARTS::NOSE, BODY_18_PARTS::RIGHT_EYE
        },
        {
            BODY_18_PARTS::RIGHT_EYE, BODY_18_PARTS::RIGHT_EAR
        },
        {
            BODY_18_PARTS::NOSE, BODY_18_PARTS::LEFT_EYE
        },
        {
            BODY_18_PARTS::LEFT_EYE, BODY_18_PARTS::LEFT_EAR
        }
    };

    /**
     * \ingroup Body_group
     * \brief Lists links of human body keypoints for \ref BODY_FORMAT "sl::BODY_FORMAT::BODY_34".
     * \n Useful for display.
     */
    const std::vector<std::pair<BODY_34_PARTS, BODY_34_PARTS>> BODY_34_BONES
    {
        {
            BODY_34_PARTS::PELVIS, BODY_34_PARTS::NAVAL_SPINE
        },
        {
            BODY_34_PARTS::NAVAL_SPINE, BODY_34_PARTS::CHEST_SPINE
        },
        {
            BODY_34_PARTS::CHEST_SPINE, BODY_34_PARTS::LEFT_CLAVICLE
        },
        {
            BODY_34_PARTS::LEFT_CLAVICLE, BODY_34_PARTS::LEFT_SHOULDER
        },
        {
            BODY_34_PARTS::LEFT_SHOULDER, BODY_34_PARTS::LEFT_ELBOW
        },
        {
            BODY_34_PARTS::LEFT_ELBOW, BODY_34_PARTS::LEFT_WRIST
        },
        {
            BODY_34_PARTS::LEFT_WRIST, BODY_34_PARTS::LEFT_HAND
        },
        {
            BODY_34_PARTS::LEFT_HAND, BODY_34_PARTS::LEFT_HANDTIP
        },
        {
            BODY_34_PARTS::LEFT_WRIST, BODY_34_PARTS::LEFT_THUMB
        },
        {
            BODY_34_PARTS::CHEST_SPINE, BODY_34_PARTS::RIGHT_CLAVICLE
        },
        {
            BODY_34_PARTS::RIGHT_CLAVICLE, BODY_34_PARTS::RIGHT_SHOULDER
        },
        {
            BODY_34_PARTS::RIGHT_SHOULDER, BODY_34_PARTS::RIGHT_ELBOW
        },
        {
            BODY_34_PARTS::RIGHT_ELBOW, BODY_34_PARTS::RIGHT_WRIST
        },
        {
            BODY_34_PARTS::RIGHT_WRIST, BODY_34_PARTS::RIGHT_HAND
        },
        {
            BODY_34_PARTS::RIGHT_HAND, BODY_34_PARTS::RIGHT_HANDTIP
        },
        {
            BODY_34_PARTS::RIGHT_WRIST, BODY_34_PARTS::RIGHT_THUMB
        },
        {
            BODY_34_PARTS::PELVIS, BODY_34_PARTS::LEFT_HIP
        },
        {
            BODY_34_PARTS::LEFT_HIP, BODY_34_PARTS::LEFT_KNEE
        },
        {
            BODY_34_PARTS::LEFT_KNEE, BODY_34_PARTS::LEFT_ANKLE
        },
        {
            BODY_34_PARTS::LEFT_ANKLE, BODY_34_PARTS::LEFT_FOOT
        },
        {
            BODY_34_PARTS::PELVIS, BODY_34_PARTS::RIGHT_HIP
        },
        {
            BODY_34_PARTS::RIGHT_HIP, BODY_34_PARTS::RIGHT_KNEE
        },
        {
            BODY_34_PARTS::RIGHT_KNEE, BODY_34_PARTS::RIGHT_ANKLE
        },
        {
            BODY_34_PARTS::RIGHT_ANKLE, BODY_34_PARTS::RIGHT_FOOT
        },
        {
            BODY_34_PARTS::CHEST_SPINE, BODY_34_PARTS::NECK
        },
        {
            BODY_34_PARTS::NECK, BODY_34_PARTS::HEAD
        },
        {
            BODY_34_PARTS::HEAD, BODY_34_PARTS::NOSE
        },
        {
            BODY_34_PARTS::NOSE, BODY_34_PARTS::LEFT_EYE
        },
        {
            BODY_34_PARTS::LEFT_EYE, BODY_34_PARTS::LEFT_EAR
        },
        {
            BODY_34_PARTS::NOSE, BODY_34_PARTS::RIGHT_EYE
        },
        {
            BODY_34_PARTS::RIGHT_EYE, BODY_34_PARTS::RIGHT_EAR
        },
        {
            BODY_34_PARTS::LEFT_ANKLE, BODY_34_PARTS::LEFT_HEEL
        },
        {
            BODY_34_PARTS::RIGHT_ANKLE, BODY_34_PARTS::RIGHT_HEEL
        },
        {
            BODY_34_PARTS::LEFT_HEEL, BODY_34_PARTS::LEFT_FOOT
        },
        {
            BODY_34_PARTS::RIGHT_HEEL, BODY_34_PARTS::RIGHT_FOOT
        }
    };

    /**
     * \ingroup Body_group
     * \brief Lists links of human body keypoints for \ref BODY_FORMAT "sl::BODY_FORMAT::BODY_38".
     * \n Useful for display.
     */
    const std::vector<std::pair<BODY_38_PARTS, BODY_38_PARTS>> BODY_38_BONES
    {
        {
            BODY_38_PARTS::PELVIS, BODY_38_PARTS::SPINE_1
        },
        {
            BODY_38_PARTS::SPINE_1, BODY_38_PARTS::SPINE_2
        },
        {
            BODY_38_PARTS::SPINE_2, BODY_38_PARTS::SPINE_3
        },
        {
            BODY_38_PARTS::SPINE_3, BODY_38_PARTS::NECK
        },
        // Face
        {
            BODY_38_PARTS::NECK, BODY_38_PARTS::NOSE
        },
        {
            BODY_38_PARTS::NOSE, BODY_38_PARTS::LEFT_EYE
        },
        {
            BODY_38_PARTS::LEFT_EYE, BODY_38_PARTS::LEFT_EAR
        },
        {
            BODY_38_PARTS::NOSE, BODY_38_PARTS::RIGHT_EYE
        },
        {
            BODY_38_PARTS::RIGHT_EYE, BODY_38_PARTS::RIGHT_EAR
        },
        // Left arm
        {
            BODY_38_PARTS::SPINE_3, BODY_38_PARTS::LEFT_CLAVICLE
        },
        {
            BODY_38_PARTS::LEFT_CLAVICLE, BODY_38_PARTS::LEFT_SHOULDER
        },
        {
            BODY_38_PARTS::LEFT_SHOULDER, BODY_38_PARTS::LEFT_ELBOW
        },
        {
            BODY_38_PARTS::LEFT_ELBOW, BODY_38_PARTS::LEFT_WRIST
        },
        {
            BODY_38_PARTS::LEFT_WRIST, BODY_38_PARTS::LEFT_HAND_THUMB_4
        },
        {
            BODY_38_PARTS::LEFT_WRIST, BODY_38_PARTS::LEFT_HAND_INDEX_1
        },
        {
            BODY_38_PARTS::LEFT_WRIST, BODY_38_PARTS::LEFT_HAND_MIDDLE_4
        },
        {
            BODY_38_PARTS::LEFT_WRIST, BODY_38_PARTS::LEFT_HAND_PINKY_1
        },
        // Right arm
        {
            BODY_38_PARTS::SPINE_3, BODY_38_PARTS::RIGHT_CLAVICLE
        },
        {
            BODY_38_PARTS::RIGHT_CLAVICLE, BODY_38_PARTS::RIGHT_SHOULDER
        },
        {
            BODY_38_PARTS::RIGHT_SHOULDER, BODY_38_PARTS::RIGHT_ELBOW
        },
        {
            BODY_38_PARTS::RIGHT_ELBOW, BODY_38_PARTS::RIGHT_WRIST
        },
        {
            BODY_38_PARTS::RIGHT_WRIST, BODY_38_PARTS::RIGHT_HAND_THUMB_4
        },
        {
            BODY_38_PARTS::RIGHT_WRIST, BODY_38_PARTS::RIGHT_HAND_INDEX_1
        },
        {
            BODY_38_PARTS::RIGHT_WRIST, BODY_38_PARTS::RIGHT_HAND_MIDDLE_4
        },
        {
            BODY_38_PARTS::RIGHT_WRIST, BODY_38_PARTS::RIGHT_HAND_PINKY_1
        },
        // Left leg
        {
            BODY_38_PARTS::PELVIS, BODY_38_PARTS::LEFT_HIP
        },
        {
            BODY_38_PARTS::LEFT_HIP, BODY_38_PARTS::LEFT_KNEE
        },
        {
            BODY_38_PARTS::LEFT_KNEE, BODY_38_PARTS::LEFT_ANKLE
        },
        {
            BODY_38_PARTS::LEFT_ANKLE, BODY_38_PARTS::LEFT_HEEL
        },
        {
            BODY_38_PARTS::LEFT_ANKLE, BODY_38_PARTS::LEFT_BIG_TOE
        },
        {
            BODY_38_PARTS::LEFT_ANKLE, BODY_38_PARTS::LEFT_SMALL_TOE
        },
        // Right leg
        {
            BODY_38_PARTS::PELVIS, BODY_38_PARTS::RIGHT_HIP
        },
        {
            BODY_38_PARTS::RIGHT_HIP, BODY_38_PARTS::RIGHT_KNEE
        },
        {
            BODY_38_PARTS::RIGHT_KNEE, BODY_38_PARTS::RIGHT_ANKLE
        },
        {
            BODY_38_PARTS::RIGHT_ANKLE, BODY_38_PARTS::RIGHT_HEEL
        },
        {
            BODY_38_PARTS::RIGHT_ANKLE, BODY_38_PARTS::RIGHT_BIG_TOE
        },
        {
            BODY_38_PARTS::RIGHT_ANKLE, BODY_38_PARTS::RIGHT_SMALL_TOE
        },
    };

    /**
    \ingroup Object_group
    \brief Class containing batched data of a detected objects from the object detection module.

    This class can be used to store trajectories.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ ObjectsBatch {
    public:
        /**
        \brief Id of the batch.
         */
        int id;

        /**
        \brief Objects class/category to identify the object type.
         */
        OBJECT_CLASS label;

        /**
        \brief Objects sub-class/sub-category to identify the object type.
         */
        OBJECT_SUBCLASS sublabel;

        /**
        \brief Objects tracking state.
         */
        OBJECT_TRACKING_STATE tracking_state;

        /**
        \brief Vector of positions for each object.
         */
        std::vector<sl::float3> positions;

        /**
        \brief Vector of positions' covariances for each object.
         */
        std::vector<std::array<float, 6 >> position_covariances;

        /**
        \brief Vector of 3D velocities for each object.
         */
        std::vector<sl::float3> velocities;

        /**
        \brief Vector of timestamps for each object.
         */
        std::vector<sl::Timestamp> timestamps;

        /**
        \brief Vector of 3D bounding boxes for each object.
        \note They are defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
        \code
           1 ------ 2
          /        /|
         0 ------ 3 |
         | Object | 6
         |        |/
         4 ------ 7
        \endcode
         */
        std::vector<std::vector<sl::float3>> bounding_boxes;

        /**
        \brief Vector of 2D bounding boxes for each object.
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
        \code
         A ------ B
         | Object |
         D ------ C
        \endcode
         */
        std::vector<std::vector<sl::uint2>> bounding_boxes_2d;

        /**
        \brief Vector of confidences for each object.
         */
        std::vector<float> confidences;

        /**
        \brief Vector of action states for each object.
         */
        std::vector<OBJECT_ACTION_STATE> action_states;

        /**
        \brief Vector of 2D bounding box of the head for each object (person).
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
        \warning Not available with [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_XXX](\ref OBJECT_DETECTION_MODEL).
         */
        std::vector<std::vector<sl::uint2>> head_bounding_boxes_2d;

        /**
        \brief Vector of 3D bounding box of the head for each object (person).
        \note They are defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
        \warning Not available with [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_XXX](\ref OBJECT_DETECTION_MODEL).
         */
        std::vector<std::vector<sl::float3>> head_bounding_boxes;

        /**
        \brief Vector of 3D centroid of the head for each object (person).
        \note They are defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
        \warning Not available with [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_XXX](\ref OBJECT_DETECTION_MODEL).
         */
        std::vector<sl::float3> head_positions;
    };

    /**
    \ingroup Body_group
    \brief Class containing batched data of a detected bodies/persons from the body tracking module.
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ BodiesBatch {
    public:
        /**
        \brief Id of the batch.
         */
        int id;

        /**
        \brief Bodies/persons tracking state.
         */
        OBJECT_TRACKING_STATE tracking_state;

        /**
        \brief Vector of positions for each body/person.
         */
        std::vector<sl::float3> positions;

        /**
        \brief Vector of positions' covariances for each body/person.
         */
        std::vector<std::array<float, 6 >> position_covariances;

        /**
        \brief Vector of 3D velocities for each body/person.
         */
        std::vector<sl::float3> velocities;

        /**
        \brief Vector of timestamps for each body/person.
         */
        std::vector<sl::Timestamp> timestamps;

        /**
        \brief Vector of 3D bounding boxes for each body/person.
        \note They are defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
        \code
           1 ------ 2
          /        /|
         0 ------ 3 |
         | Object | 6
         |        |/
         4 ------ 7
        \endcode
         */
        std::vector<std::vector<sl::float3>> bounding_boxes;

        /**
        \brief Vector of 2D bounding boxes for each body/person.
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
        \code
         A ------ B
         | Object |
         D ------ C
        \endcode
         */
        std::vector<std::vector<sl::uint2>> bounding_boxes_2d;

        /**
        \brief Vector of confidences for each body/person.
         */
        std::vector<float> confidences;

        /**
        \brief Vector of action states for each body/person.
         */
        std::vector<OBJECT_ACTION_STATE> action_states;

        /**
        \brief Vector of 2D keypoints for each body/person.
        \warning In some cases, eg. body partially out of the image or missing depth data, some keypoints can not be detected. They will have non finite values.
         */
        std::vector<std::vector<sl::float2>> keypoints_2d;

        /**
        \brief Vector of 3D keypoints for each body/person.
        \warning In some cases, eg. body partially out of the image or missing depth data, some keypoints can not be detected. They will have non finite values.
         */
        std::vector<std::vector<sl::float3>> keypoints;

        /**
        \brief Vector of 2D bounding box of the head for each body/person.
        \note Expressed in pixels on the original image resolution, ```[0, 0]``` is the top left corner.
         */
        std::vector<std::vector<sl::uint2>> head_bounding_boxes_2d;

        /**
        \brief Vector of 3D bounding box of the head for each body/person.
        \note They are defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        std::vector<std::vector<sl::float3>> head_bounding_boxes;

        /**
        \brief Vector of 3D centroid of the head for each body/person.
        \note They are defined in sl::InitParameters.coordinate_units and expressed in sl::RuntimeParameters.measure3D_reference_frame.
         */
        std::vector<sl::float3> head_positions;

        /**
        \brief Vector of detection confidences vector for each keypoint for each body/person.
        \note They can not be lower than the sl::BodyTrackingRuntimeParameters.detection_confidence_threshold.
        \warning In some cases, eg. body partially out of the image or missing depth data, some keypoints can not be detected. They will have non finite values.
         */
        std::vector<std::vector<float>> keypoint_confidences;
    };

    /**
    \class CommunicationParameters
    \ingroup Fusion_group

    \brief Holds the communication parameter to configure the connection between senders and receiver
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ CommunicationParameters {
    public:

        /**
        \enum COMM_TYPE
        \brief Lists the different types of communications available for Fusion module.
         */
        enum class COMM_TYPE {
            LOCAL_NETWORK, /**< The sender and receiver are on the same local network and communicate by RTP.\n The communication can be affected by the local network load.*/
            INTRA_PROCESS, /**< Both sender and receiver are declared by the same process and can be in different threads.\n This type of communication is optimized.*/
            ///@cond SHOWHIDDEN 
            LAST
            ///@endcond
        };

        /**
        \brief Default constructor. All the parameters are set to their default and optimized values.
         */
        CommunicationParameters();

        /**
        \brief Setup the communication to used shared memory for intra process workflow, senders and receiver in different threads.
         */
        void setForSharedMemory();

        /**
        \brief Setup local Network connection information, sender side, only the port is required
         */
        void setForLocalNetwork(int port);

        /**
        \brief Setup local Network connection information, receiver side, need the edge device IP and the port
         */
        void setForLocalNetwork(std::string ip_address, int port);

        /**
         * @brief This function returns the comm port used for streaming the data
         * \return the port
         */
        int getPort() {
            return ip_port;
        }

        /**
         * @brief This function returns the IP address of the sender
         * \return the IP address
         */
        std::string getIpAddress() {
            return ip_add;
        }

        /**
         * @brief  This function returns the type of the used communication
         * \return the \ref COMM_TYPE of the communication used
         */
        COMM_TYPE getType() {
            return communication_type;
        }

    private:
        COMM_TYPE communication_type;
        int ip_port;
        std::string ip_add;
    };

    /*
    \struct SVOData
    \ingroup Depth_group
    \brief Structure containing data that can be stored in and retrieved from SVOs.

    That information will be ingested with sl::Camera.ingestDataIntoSVO and retrieved with sl::Camera.retrieveSVOData.

    */
    struct /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ SVOData {

        SVOData(std::string& key_, std::vector<uint8_t>& content_, sl::Timestamp timestamp_ns_ = 0) {
            key = key_;
            content = content_;
            timestamp_ns = timestamp_ns_;
        }

        SVOData() {
            content = std::vector<uint8_t>();
        }

    public:
        /**
        \brief Set a std::string into the SVOData's content.
         */
        bool setContent(const std::string &s)
        {
            content = std::vector<uint8_t>(s.begin(), s.end());
            return true;
        }

        /**
        \brief Retrieve the SVOData content as a std::string.
         */
        bool getContent(std::string &s) const
        {
            s = std::string(content.begin(), content.end());
            return true;
        }

        std::string key;
        sl::Timestamp timestamp_ns = 0;
        std::vector<uint8_t> content; // allow any type of content, including raw data like compressed images or json
    };
}
#endif /* __CORE_HPP__ */
#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>
#include <memory>


#if defined(_WIN32)
#ifdef CORE_COMPILATION
#define SL_SCANNING_EXPORT __declspec(dllexport)
#else
#define SL_SCANNING_EXPORT
#endif
#elif __GNUC__
#define SL_SCANNING_EXPORT __attribute__((visibility("default")))
#else
#define SL_SCANNING_EXPORT
#endif

namespace sl {

    /**
    \enum MESH_FILE_FORMAT
    \ingroup SpatialMapping_group
    \brief Lists available mesh file formats.
     */
    enum class MESH_FILE_FORMAT {
        PLY, /**< Contains only vertices and faces.*/
        PLY_BIN, /**< Contains only vertices and faces encoded in binary.*/
        OBJ, /**< Contains vertices, normals, faces, and texture information (if possible).*/
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond        
    };

    ///@cond SHOWHIDDEN
    String /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ toString(const MESH_FILE_FORMAT &mesh_frmt);

    inline std::ostream &operator<<(std::ostream &os, const MESH_FILE_FORMAT &mesh_frmt) {
        return os << toString(mesh_frmt);
    }
    ///@endcond

    /**
    \enum MESH_TEXTURE_FORMAT
    \ingroup SpatialMapping_group
    \brief Lists available mesh texture formats.
     */
    enum class MESH_TEXTURE_FORMAT {
        RGB, /**< The texture will be on 3 channels.*/
        RGBA, /**< The texture will be on 4 channels.*/
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ toString(const MESH_TEXTURE_FORMAT &text_frmt);

    inline std::ostream &operator<<(std::ostream &os, const MESH_TEXTURE_FORMAT &text_frmt) {
        return os << toString(text_frmt);
    }
    ///@endcond

    /**
    \class MeshFilterParameters
    \ingroup SpatialMapping_group
    \brief Class containing a set of parameters for the [mesh filtration](\ref Mesh::filter) functionality.

    The default constructor sets all parameters to their default settings.
    \note Parameters can be adjusted by the user.
     */
    class /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ MeshFilterParameters {
    public:

        /**
        \enum MESH_FILTER.
        \ingroup SpatialMapping_group
        \brief Lists available mesh filtering intensities.
         */
        enum class MESH_FILTER {
            LOW, /**< Clean the mesh by closing small holes and removing isolated faces.*/
            MEDIUM, /**< Soft faces decimation and smoothing.*/
            HIGH, /**< Drastically reduce the number of faces and apply a soft smooth.*/
            ///@cond SHOWHIDDEN 
            LAST
            ///@endcond
        };

        /**
        \brief Default constructor.
        
        All the parameters are set to their default values.
         */
        MeshFilterParameters(MESH_FILTER mesh_filtering = MESH_FILTER::LOW) {
            set(mesh_filtering);
        }

        /**
        \brief Sets the filtering intensity.
        \param mesh_filtering : Desired sl::MeshFilterParameters::MESH_FILTER.
         */
        void set(MESH_FILTER mesh_filtering = MESH_FILTER::LOW) {
            filtering = mesh_filtering;
        }

        /**
        \brief Filtering intensity.
         */
        MESH_FILTER filtering = MESH_FILTER::LOW;

        /**
        \brief Saves the current set of parameters into a file to be reloaded with the \ref load() method.
        \param filename : Name of the file which will be created to store the parameters.
        \return True if the file was successfully saved, otherwise false.
        \warning For security reasons, the file must not already exist.
        \warning In case a file already exists, the method will return false and existing file will not be updated.
         */
        bool save(String filename);

        /**
        \brief Loads a set of parameters from the values contained in a previously \ref save() "saved" file.
        \param filename : Path to the file from which the parameters will be loaded.
        \return True if the file was successfully loaded, otherwise false.
         */
        bool load(String filename);
    };

    ///@cond SHOWHIDDEN
    String /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ toString(const MeshFilterParameters::MESH_FILTER &mesh_filter);

    inline std::ostream &operator<<(std::ostream &os, const MeshFilterParameters::MESH_FILTER &mesh_filter) {
        return os << toString(mesh_filter);
    }
    ///@endcond

    /*@cond SHOWHIDDEN*/
    enum class MESH_CREATION {
        NONE,
        LIVE,
        LOAD
    };

    class SL_CORE_EXPORT TextureImagePool {
    public:
        TextureImagePool();
        ~TextureImagePool();

        inline bool isEmpty() {
            return v.size() == 0;
        }

        std::vector<std::pair<sl::Mat *, sl::Transform>> v;
        void clear();
        void init(sl::Resolution res);
        void emplace_back(sl::Mat &im_gpu, sl::Transform path);

    private:
        sl::Resolution resolution;
    };
    /*@endcond*/

    /**
    \class Chunk
    \ingroup SpatialMapping_group
    \brief Class representing a sub-mesh containing local vertices and triangles.

    Vertices and normals have the same size and are linked by id stored in triangles.
    \note \ref uv contains data only if your mesh have textures (by loading it or after calling sl::Mesh.applyTexture()).
     */
    class /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ Chunk {
    public:
        /**
        \brief Default constructor.
        
        Creates an empty sl::Chunk.
         */
        Chunk();

        /**
        \brief Default destructor.
         */
        ~Chunk();

        /**
        \brief Vector of vertices.

        Vertices are defined by a 3D point ```{x, y, z}```.
         */
        std::vector<float3> vertices;

        /**
        \brief Vector of triangles/faces.

        Triangles are defined as a set of three vertices indexes ```{v1, v2, v3}```.
         */
        std::vector<uint3> triangles;

        /**
        \brief Vector of normals.

        Normals are defined by three components ```{nx, ny, nz}```.
        \note A normal is defined for each vertex.
         */
        std::vector<float3> normals;

        /**
        \brief Vector of colors.

        Colors are defined by three components ```{b, g, r}```.
        \note A color is defined for each vertex.
         */
        std::vector<uchar3> colors;

        /**
        \brief UVs defines the 2D projection of each vertices onto the texture.

        Values are normalized [0, 1] and start from the bottom left corner of the texture (as requested by OpenGL).
        \n In order to display a textured mesh you need to bind the texture and then draw each triangle by picking its uv values.
        \note Contains data only if your mesh has textures (by loading it or calling sl::Mesh.applyTexture()).
         */
        std::vector<float2> uv;

        /**
        \brief Timestamp of the latest update.
         */
        unsigned long long timestamp;

        /**
        \brief 3D centroid of the chunk.
         */
        float3 barycenter;

        /**
        \brief Whether the point cloud chunk has been updated by an inner process.
         */
        bool has_been_updated;

        /**
        \brief Clears all data.
         */
        void clear();
    };

    /**
    \class Mesh
    \ingroup SpatialMapping_group
    \brief Class representing a mesh and containing the geometric (and optionally texture) data of the scene captured by the spatial mapping module.

    By default the mesh is defined as a set of chunks.
    \n This way we update only the data that has to be updated avoiding a time consuming remapping process every time a small part of the sl::Mesh is updated.
     */
    class /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ Mesh {
        ///@cond
        friend class SpatialMappingHandler;
        ///@endcond

    public:
        /**
        \brief Vector of chunks id.
        */
        typedef std::vector<size_t> chunkList;

        /**
        \brief Default constructor.
        
        Creates an empty sl::Mesh.
         */
        Mesh();

        /**
        \brief Default destructor.
         */
        ~Mesh();

        /**
        \brief Vector of chunks constituting the sl::Mesh.
         */
        std::vector<Chunk> chunks;

        /**
        \brief Vector of vertices.

        Vertices are defined by a 3D point ```{x, y, z}```.
         */
        std::vector<float3> vertices;

        /**
        \brief Vector of triangles/faces.

        Triangles are defined as a set of three vertices indexes ```{v1, v2, v3}```.
         */
        std::vector<uint3> triangles;

        /**
        \brief Vector of normals.
        
        Normals are defined by three components ```{nx, ny, nz}```.
        \note A normal is defined for each vertex.
         */
        std::vector<float3> normals;

        /**
        \brief Vector of colors.
        
        Colors are defined by three components ```{b, g, r}```.
        \note A color is defined for each vertex.
         */
        std::vector<uchar3> colors;

        /**
        \brief UVs defines the 2D projection of each vertices onto the texture.

        Values are normalized [0, 1] and start from the bottom left corner of the texture (as requested by OpenGL).
        In order to display a textured mesh you need to bind the texture and then draw each triangle by picking its uv values.
        \note Contains data only if your mesh has textures (by loading it or calling sl::Mesh.applyTexture()).
         */
        std::vector<float2> uv;

        /**
        \brief Texture of the sl::Mesh.
        \note Contains data only if your mesh has textures (by loading it or calling sl::Mesh.applyTexture()).
         */
        Mat texture;

        /**
        \brief Defines the [] operator to directly access the desired chunk.
         */
        Chunk &operator[](int index);

        /**
        \brief Computes the total number of triangles stored in all chunks.
        \return The number of triangles stored in all chunks.
         */
        size_t getNumberOfTriangles();

        /**
        \brief Updates \ref vertices / \ref normals / \ref triangles / \ref uv from chunk data pointed by the given sl::Mesh::chunkList.
        \param IDs : Indices of chunks which will be concatenated. Default: (empty).
        \note If the given sl::Mesh::chunkList is empty, all chunks will be used to update the current sl::Mesh.
         */
        void updateMeshFromChunkList(chunkList IDs = chunkList());

        /**
        \brief Computes the sl::Mesh::chunkList of visible chunks from a specific point of view.
        \param camera_pose : Point of view (given in the same reference as the vertices).
        \return The list of id of visible chunks.
         */
        chunkList getVisibleList(Transform camera_pose);

        /**
        \brief Computes the sl::Mesh::chunkList of chunks close to a specific point of view.
        \param camera_pose : Point of view (given in the same reference as the vertices).
        \param radius : Radius determining closeness (given in the same unit as the mesh).
        \return The list of id of chunks close to the given point.
         */
        chunkList getSurroundingList(Transform camera_pose, float radius);

        /**
        \brief Filters the mesh.

        The resulting mesh is smoothed, small holes are filled, and small blobs of non-connected triangles are deleted.
        \param mesh_filter_params : Filtering parameters. Default: a preset of sl::MeshFilterParameters.
        \param update_chunk_only : Whether to only update \ref chunks (and not \ref vertices / \ref normals / \ref triangles).\n Default: false.
        \return True if the mesh was successfully filtered, otherwise false.

        \note The filtering is a costly operation.
        \note It is not recommended to call it every time you retrieve a mesh but only at the end of your spatial mapping process.
         */
        bool filter(MeshFilterParameters mesh_filter_params = MeshFilterParameters(), bool update_chunk_only = false);

        /**
        \brief Applies a texture to the mesh.

        By using this method you will get access to \ref uv, and \ref texture.
        \n The number of triangles in the mesh may slightly differ before and after calling this method due to missing texture information.
        \n There is only one texture for the mesh, the uv of each chunk are expressed for it in its entirety.
        \n Vectors of \ref vertices / \ref normals and \ref uv have now the same size.

        \param texture_format : Number of channels desired for the computed texture.\n Default: [sl::MESH_TEXTURE_FORMAT::RGB](\ref MESH_TEXTURE_FORMAT).
        \return True if the mesh was successfully textured, otherwise false.

        \note This method can be called as long as you do not start a new spatial mapping process (due to shared memory).
        \note This method can require a lot of computation time depending on the number of triangles in the mesh.
        \note It is recommended to call it once at the end of your spatial mapping process.

        \warning The sl::SpatialMappingParameters.save_texture parameter must be set to true when enabling the spatial mapping to be able to apply the textures.
        \warning The mesh should be filtered before calling this method since \ref filter() will erase the textures.
        \warning The texturing is also significantly slower on non-filtered meshes.
         */
        bool applyTexture(MESH_TEXTURE_FORMAT texture_format = MESH_TEXTURE_FORMAT::RGB);

        /**
        \brief Merges current chunks.

        This method can be used to merge chunks into bigger sets to improve rendering process.
        \param faces_per_chunk : Number of faces per chunk.
        
        \note This method is useful for Unity, which does not handle chunks with more than 65K vertices.
        \warning This method should not be called during spatial mapping process since mesh updates will revert this changes.
         */
        void mergeChunks(int faces_per_chunk);

        /**
        \brief Estimates the gravity vector.

        This method looks for a dominant plane in the whole mesh considering that it is the floor (or a horizontal plane).
        \return The estimated gravity vector.

        \note This can be used to find the gravity to create realistic physical interactions.
         */
        sl::float3 getGravityEstimate();

        /**
        \brief Compute the indices of boundary vertices.
        \return The indices of boundary vertices.
         */
        std::vector<int> getBoundaries();

        /**
        \brief Saves the current sl::Mesh into a file.
        \param filename : Path of the file to store the mesh in.
        \param type : File extension type. Default: [sl::MESH_FILE_FORMAT::OBJ](\ref MESH_FILE_FORMAT).
        \param IDs : Set of chunks to be saved. Default: (empty) (all chunks are saved)
        \return True if the file was successfully saved, otherwise false.

        \note Only [sl::MESH_FILE_FORMAT::OBJ](\ref MESH_FILE_FORMAT) support textures data.
        \note This method operates on the sl.Mesh not on \ref chunks.
        \note This way you can save different parts of your sl.Mesh by updating it with \ref updateMeshFromChunkList().
         */
        bool save(String filename, MESH_FILE_FORMAT type = MESH_FILE_FORMAT::OBJ, chunkList IDs = chunkList());

        /**
        \brief Loads the mesh from a file.
        \param filename : Path of the file to load the mesh from.
        \param update_chunk_only : Whether to only load data in \ref chunks (and not \ref vertices / \ref normals / \ref triangles).\n Default: false.
        \return True if the mesh was successfully loaded, otherwise false.

        \note Updating a sl::Mesh is time consuming. Consider using only \ref chunks for better performances.
         */
        bool load(String filename, bool update_chunk_only = false);

        /**
        \brief Clears all the data.
         */
        void clear();

    private:
        void init();

        std::shared_ptr<TextureImagePool> p_im_pool;
        sl::CameraParameters cam_param;
        float min_d, max_d;
        size_t memory;
        bool face_order;
        int id_mesher; /** < used to clear the mesh based on the number of the current mesher, if different clear it */
        MESH_CREATION state;
    };

    /**
    \enum PLANE_TYPE
    \brief Lists the available plane types detected based on the orientation.
     */
    enum class PLANE_TYPE {
        HORIZONTAL, /**< Horizontal plane, such as a tabletop, floor, etc.*/
        VERTICAL, /**< Vertical plane, such as a wall.*/
        UNKNOWN, /**< Unknown plane orientation.*/
        ///@cond SHOWHIDDEN 
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ toString(const PLANE_TYPE &type);

    inline std::ostream &operator<<(std::ostream &os, const PLANE_TYPE &type) {
        return os << toString(type);
    }
    ///@endcond

    /**
    \class Plane
    \ingroup SpatialMapping_group
    \brief Class representing a plane defined by a point and a normal, or a plane equation.
    
    Other elements can be extracted such as the mesh, the 3D bounds, etc.
    \note The plane measurements are expressed in reference defined by sl::RuntimeParameters.measure3D_reference_frame.
     */

    class /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ Plane {
        ///@cond SHOWHIDDEN
        friend class PlaneCandidate;
        friend class PlaneDetectorHandler;
        ///@endcond
    public:

        /**
        \brief Default constructor.
         */
        Plane();
        /**
        \brief Default destructor.
         */
        ~Plane();

        /**
        \brief Clears all the data.
         */
        void clear();

        /**
        \brief Type of the plane defined by its orientation.
        \note It is deduced from the gravity vector and is therefore not available with on [sl::MODEL::ZED](\ref MODEL).
        \note [sl::MODEL::ZED](\ref MODEL) will give [sl::PLANE_TYPE::UNKNOWN](\ref PLANE_TYPE) for every planes.
         */
        PLANE_TYPE type = PLANE_TYPE::UNKNOWN;

        /**
        \brief Gets the plane normal vector.
        \return sl::Plane normalized normal vector.
         */
        sl::float3 getNormal();

        /**
        \brief Gets the plane center point
        \return sl::Plane center point.
         */
        sl::float3 getCenter();

        /**
        \brief Gets the plane pose relative to the global reference frame.
        \return Transformation matrix (rotation and translation) of the plane pose.
        \note Can be used to transform the global reference frame center ```(0, 0, 0)``` to the plane center.
         */
        Transform getPose();

        /**
        \brief Gets the width and height of the bounding rectangle around the plane contours.
        \return Width and height of the bounding plane contours.

        \warning This value is expressed in the plane reference frame.
         */
        sl::float2 getExtents();

        /**
        \brief Gets the plane equation.
        \return Plane equation coefficients ```{a, b, c, d}```.
        \note The plane equation has the following form: ```ax + by + cz = d```.
         */
        sl::float4 getPlaneEquation();

        /**
        \brief Gets the polygon bounds of the plane.
        \return Vector of 3D points forming a polygon bounds corresponding to the current visible limits of the plane.
         */
        std::vector<sl::float3> getBounds();

        /**
        \brief Compute and return the mesh of the bounds polygon.
        \return sl::Mesh representing the plane delimited by the visible bounds.
         */
        sl::Mesh extractMesh();

        /**
        \brief Gets the distance between the input point and the projected point alongside the normal vector onto the plane (the closest point on the plane).
        \param point : Point to project into the plane.
        \return The Euclidean distance between the input point and the projected point.
         */
        float getClosestDistance(sl::float3 point = sl::float3(0, 0, 0));
        
    private:
        std::vector<sl::float3> bounds3D_RuCu;
        std::vector<sl::float2> bounds2D;
        sl::float2 sizeRect;
        sl::Transform planePose_RuCu;

        sl::float4 e_RcCi;
        sl::Transform Rt_RcCiRuCi;
        sl::Transform pose_RcCi;

        sl::float4 planeEquation_RuCu;
        sl::Mesh mesh_RuCu;

        float coef, unit_factor;
        sl::Transform transform_Ci2Cu;
        bool isFloor;
        void computeBoundingRect(std::vector<sl::uint2> &bounds2D_RcCi, sl::float4 param);
    };

    /**
    \class PointCloudChunk
    \ingroup SpatialMapping_group
    \brief Class representing a sub-point cloud containing local vertices and colors.

    \note \ref vertices and \ref normals have the same size.
     */
    class /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ PointCloudChunk {
    public:
        /**
        \brief Default constructor.
        
        Creates an empty sl::PointCloudChunk.
         */
        PointCloudChunk();

        /**
        \brief Default destructor.
         */
        ~PointCloudChunk();

        /**
        \brief Vector of vertices.

        Vertices are defined by a colored 3D point ```{x, y, z, rgba}```.
         */
        std::vector<float4> vertices;

        /**
        \brief Vector of normals.

        Normals are defined by three components ```{nx, ny, nz}```.
         */
        std::vector<float3> normals;

        /**
        \brief Timestamp of the latest update.
         */
        unsigned long long timestamp;

        /**
        \brief 3D centroid of the chunk.
         */
        float3 barycenter;

        /**
        \brief Whether the chunk has been updated by an inner process.
         */
        bool has_been_updated;

        /**
        \brief Clears all data.
         */
        void clear();
    };

    /**
    \class FusedPointCloud
    \ingroup SpatialMapping_group
    \brief Class representing a fused point cloud and containing the geometric and color data of the scene captured by the spatial mapping module.

    By default the fused point cloud is defined as a set of point cloud chunks.
    \n This way we update only the required data, avoiding a time consuming remapping process every time a small part of the sl::FusedPointCloud cloud is changed.
     */
    class /*@cond SHOWHIDDEN*/SL_SCANNING_EXPORT/*@endcond*/ FusedPointCloud {
        ///@cond
        friend class SpatialMappingHandler;
        ///@endcond

    public:
        /**
        \brief Vector of chunks id.
        */
        typedef std::vector<size_t> chunkList;

        /**
        \brief Default constructor.
        
        Creates an empty sl::FusedPointCloud.
         */
        FusedPointCloud();

        /**
        \brief Default destructor.
         */
        ~FusedPointCloud();

        /**
        \brief List of chunks constituting the sl::FusedPointCloud.
         */
        std::vector<PointCloudChunk> chunks;

        /**
        \brief Vector of vertices.

        Vertices are defined by a colored 3D point ```{x, y, z, rgba}```.
         */
        std::vector<float4> vertices;

        /**
        \brief Vector of normals.

        Normals are defined by three components ```{nx, ny, nz}```.
         */
        std::vector<float3> normals;

        /**
        \brief Defines the [] operator to directly access the desired chunk.
         */
        PointCloudChunk &operator[](int index);

        /**
        \brief Computes the total number of points stored in all chunks.
        \return The number of points stored in all chunks.
         */
        size_t getNumberOfPoints();

        /**
        \brief Updates \ref vertices and \ref normals from chunk data pointed by the given sl::Mesh::chunkList.
        \param IDs : Indices of chunks which will be concatenated. Default: (empty).

        \note If the given sl::FusedPointCloud::chunkList is empty, all chunks will be used to update the current sl::FusedPointCloud.
         */
        void updateFromChunkList(chunkList IDs = chunkList());

        /**
        \brief Saves the current sl::FusedPointCloud into a file.
        \param filename : Path of the file to store the fused point cloud in.
        \param type : File extension type. Default: [sl::MESH_FILE_FORMAT::OBJ](\ref MESH_FILE_FORMAT).
        \param IDs : Set of chunks to be saved. Default: (empty) (all chunks are saved)
        \return True if the file was successfully saved, otherwise false.

        \note This method operates on the sl::FusedPointCloud not on \ref chunks.
        \note This way you can save different parts of your sl::FusedPointCloud by updating it with \ref updateFromChunkList().
         */
        bool save(String filename, MESH_FILE_FORMAT type = MESH_FILE_FORMAT::OBJ, chunkList IDs = chunkList());

        /**
        \brief Loads the fused point cloud from a file.
        \param filename : Path of the file to load the fused point cloud from.
        \param update_chunk_only : Whether to only load data in \ref chunks (and not \ref vertices / \ref normals).\n Default: false.
        \return True if the mesh was successfully loaded, otherwise false.

        \note Updating a sl::FusedPointCloud is time consuming. Consider using only \ref chunks for better performances.
         */
        bool load(String filename, bool update_chunk_only = false);

        /**
        \brief Clears all the data.
         */
        void clear();

    private:
        void init();

        sl::CameraParameters cam_param;
        float min_d, max_d;
        size_t memory;
        int id_mesher; /** < used to clear the mesh based on the number of the current mesher, if different clear it */
        MESH_CREATION state;
    };


}

#endif /* MESH_HPP_ */
#ifndef __DEFINES_HPP__
#define __DEFINES_HPP__


#if defined _WIN32
#if defined(SL_SDK_COMPIL)
#define SL_SDK_EXPORT __declspec(dllexport)
#else
#define SL_SDK_EXPORT __declspec(dllimport)
#endif
#elif __GNUC__
#define SL_SDK_EXPORT __attribute__((visibility("default")))
#if defined(__arm__) || defined(__aarch64__)
#define _SL_JETSON_
#endif
#endif

// SDK VERSION NUMBER
#define ZED_SDK_MAJOR_VERSION 4
#define ZED_SDK_MINOR_VERSION 1
#define ZED_SDK_PATCH_VERSION 3

#define ZED_SDK_BUILD_ID "91256_6aa9ad15"

#define ZED_SDK_VERSION_ATTRIBUTE private: uint32_t _zed_sdk_major_version = ZED_SDK_MAJOR_VERSION, _zed_sdk_minor_version = ZED_SDK_MINOR_VERSION, _zed_sdk_patch_version = ZED_SDK_PATCH_VERSION;

/**
 * \ingroup Core_group
 * \brief Returns the ZED SDK version currently installed on the computer.
 * \param major[out] : Major variable to be filled.
 * \param minor[out] : Minor variable to be filled.
 * \param patch[out] : Patch variable to be filled.
 * \return -1 if the ZED SDK was not found
 * \return -2 if the ZED SDK version wasn't found
 * \return 0 if success
 */
int /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ getZEDSDKRuntimeVersion(int &major, int& minor, int& patch);

extern "C" {

    int /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ getZEDSDKRuntimeVersion_C(int &major, int& minor, int& patch);

    /**
    \ingroup Core_group
    \brief Returns the ZED SDK version which the current program has been compiled with.
    \param major[out] : Major variable to be filled.
    \param minor[out] : Minor variable to be filled.
    \param patch[out] : Patch variable to be filled.
     */
    inline const void /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ getZEDSDKBuildVersion(int &major, int& minor, int& patch) {
        major = ZED_SDK_MAJOR_VERSION;
        minor = ZED_SDK_MINOR_VERSION;
        patch = ZED_SDK_PATCH_VERSION;
    }
}

namespace sl {

    ///@{
    ///  @name Unavailable Values
    /**
    Defines an unavailable depth value that is above the depth Max value.
     */
    static const float TOO_FAR = INFINITY;
    /**
    Defines an unavailable depth value that is below the depth Min value.
     */
    static const float TOO_CLOSE = -INFINITY;
    /**
    Defines an unavailable depth value that is on an occluded image area.
     */
    static const float OCCLUSION_VALUE = NAN;
    ///@}

    static const float INVALID_VALUE = NAN;

    static const unsigned char STATIC_DEPTH = 255;
    static const unsigned char DYNAMIC_DEPTH = 127;

    //macro to detect wrong data measure
#define isValidMeasure(v) (std::isfinite(v))

    /// \defgroup Video_group Video Module
    /// \defgroup Depth_group Depth Sensing Module
    /// \defgroup Core_group Core Module
    /// \defgroup SpatialMapping_group Spatial Mapping Module
    /// \defgroup PositionalTracking_group Positional Tracking Module
    /// \defgroup Object_group Object Detection Module
    /// \defgroup Body_group Body Tracking Module
    /// \defgroup Sensors_group Sensors Module
    /// \defgroup Fusion_group Fusion Module

    /**
    \enum SIDE
    \ingroup Video_group
    \brief Lists possible sides on which to get data from.
     */
    enum class SIDE {
        LEFT, /**< Left side only.*/
        RIGHT, /**< Right side only.*/
        BOTH /**< Left and right side.*/
    };

    /**
    \enum FLIP_MODE
    \ingroup Video_group
    \brief Lists possible flip modes of the camera.
     */
    enum FLIP_MODE : int {
        OFF = 0, /**< No flip applied. Default behavior.*/
        ON = 1, /**< Images and camera sensors' data are flipped useful when your camera is mounted upside down.*/
        AUTO = 2, /**< In LIVE mode, use the camera orientation (if an IMU is available) to set the flip mode.\n In SVO mode, read the state of this enum when recorded.*/
        ///@cond SHOWHIDDEN
        LAST = 3
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ toString(const FLIP_MODE& flip_mode);

    inline ::std::ostream& operator<<(::std::ostream& os, const FLIP_MODE& flip_mode) {
        return os << toString(flip_mode);
    }
    ///@endcond

    /**
    \enum RESOLUTION
    \ingroup Video_group
    \brief Lists available resolutions.
    \note The VGA resolution does not respect the 640*480 standard to better fit the camera sensor (672*376 is used).
    \warning All resolutions are not available for every camera.
    \warning You can find the available resolutions for each camera in <a href="https://www.stereolabs.com/docs/video/camera-controls#selecting-a-resolution">our documentation</a>.
     */
    enum class RESOLUTION {
        HD4K, /**< 3856x2180 for imx678 mono*/
        HD2K, /**< 2208*1242 (x2) \n Available FPS: 15*/
        HD1080, /**< 1920*1080 (x2) \n Available FPS: 15, 30*/
        HD1200, /**< 1920*1200 (x2) \n Available FPS: 15, 30, 60*/
        HD720, /**< 1280*720 (x2) \n Available FPS: 15, 30, 60*/
        SVGA, /**< 960*600 (x2) \n Available FPS: 15, 30, 60, 120*/
        VGA, /**< 672*376 (x2) \n Available FPS: 15, 30, 60, 100*/
        AUTO, /**< Select the resolution compatible with the camera: <ul><li>ZED X/X Mini: HD1200</li><li>other cameras: HD720</li></ul> */
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const RESOLUTION &resolution);

    inline ::std::ostream &operator<<(::std::ostream &os, const RESOLUTION &resolution) {
        return os << toString(resolution);
    }
    ///@endcond

    /**
    \ingroup Video_group
    \brief Gets the corresponding sl::Resolution from an sl::RESOLUTION.
    \param resolution : The wanted sl::RESOLUTION.
    \return The sl::Resolution corresponding to sl::RESOLUTION given as argument.
     */
    sl::Resolution /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ getResolution(RESOLUTION resolution);

    /**
    \enum VIDEO_SETTINGS
    \ingroup Video_group
    \brief Lists available camera settings for the camera (contrast, hue, saturation, gain, ...).
    \warning All \ref VIDEO_SETTINGS are not supported for all camera models. You can find the supported \ref VIDEO_SETTINGS for each ZED camera in our <a href="https://www.stereolabs.com/docs/video/camera-controls#adjusting-camera-settings">documentation</a>.\n\n
     GAIN and EXPOSURE are linked in auto/default mode (see \ref sl::Camera.setCameraSettings()).
     */
    enum class VIDEO_SETTINGS {
        BRIGHTNESS, /**< Brightness control \n Affected value should be between 0 and 8. \note Not available for ZED X/X Mini cameras.*/
        CONTRAST, /**< Contrast control \n Affected value should be between 0 and 8. \note Not available for ZED X/X Mini cameras.*/
        HUE, /**< Hue control \n Affected value should be between 0 and 11. \note Not available for ZED X/X Mini cameras.*/
        SATURATION, /**< Saturation control \n Affected value should be between 0 and 8.*/
        SHARPNESS, /**< Digital sharpening control \n Affected value should be between 0 and 8.*/
        GAMMA, /**< ISP gamma control \n Affected value should be between 1 and 9.*/
        GAIN, /**< Gain control \n Affected value should be between 0 and 100 for manual control. \note If EXPOSURE is set to -1 (automatic mode), then GAIN will be automatic as well.*/
        EXPOSURE, /**< Exposure control \n Affected value should be between 0 and 100 for manual control.\n The exposition is mapped linearly in a percentage of the following max values.\n Special case for <code>EXPOSURE = 0</code> that corresponds to 0.17072ms.\n The conversion to milliseconds depends on the framerate: <ul><li>15fps & <code>EXPOSURE = 100</code> -> 19.97ms</li><li>30fps & <code>EXPOSURE = 100</code> -> 19.97ms</li><li>60fps & <code>EXPOSURE = 100</code> -> 10.84072ms</li><li>100fps & <code>EXPOSURE = 100</code> -> 10.106624ms</li></ul>*/
        AEC_AGC, /**< Defines if the GAIN and EXPOSURE are in automatic mode or not.\n Setting GAIN or EXPOSURE values will automatically set this value to 0.*/
        AEC_AGC_ROI, /**< Defines the region of interest for automatic exposure/gain computation.\n To be used with overloaded \ref Camera.setCameraSettings(VIDEO_SETTINGS,Rect,sl::SIDE,bool) "setCameraSettings()" / \ref Camera.getCameraSettings(VIDEO_SETTINGS,Rect&,sl::SIDE) "getCameraSettings()" methods.*/
        WHITEBALANCE_TEMPERATURE, /**< Color temperature control \n Affected value should be between 2800 and 6500 with a step of 100. \note Setting a value will automatically set WHITEBALANCE_AUTO to 0.*/
        WHITEBALANCE_AUTO, /**< Defines if the white balance is in automatic mode or not.*/
        LED_STATUS, /**< Status of the front LED of the camera.\n Set to 0 to disable the light, 1 to enable the light.\n Default value is on. \note Requires camera firmware 1523 at least.*/
        EXPOSURE_TIME, /**< Real exposure time control in microseconds. \note Only available for ZED X/X Mini cameras.\note Replace EXPOSURE setting.*/
        ANALOG_GAIN, /**< Real analog gain (sensor) control in mDB.\n The range is defined by Jetson DTS and by default [1000-16000]. \note Only available for ZED X/X Mini cameras.\note Replace GAIN settings.*/
        DIGITAL_GAIN, /**< Real digital gain (ISP) as a factor.\n The range is defined by Jetson DTS and by default [1-256]. \note Only available for ZED X/X Mini cameras.\note Replace GAIN settings.*/
        AUTO_EXPOSURE_TIME_RANGE, /**< Range of exposure auto control in microseconds.\n Used with \ref Camera.setCameraSettings(VIDEO_SETTINGS,int,int) "setCameraSettings()".\n Min/max range between max range defined in DTS.\n By default: [28000 - <fps_time> or 19000] us. \note Only available for ZED X/X Mini cameras.*/
        AUTO_ANALOG_GAIN_RANGE, /**< Range of sensor gain in automatic control.\n Used with \ref Camera.setCameraSettings(VIDEO_SETTINGS,int,int) "setCameraSettings()".\n Min/max range between max range defined in DTS.\n By default: [1000 - 16000] mdB. \note Only available for ZED X/X Mini cameras.*/
        AUTO_DIGITAL_GAIN_RANGE, /**< Range of digital ISP gain in automatic control.\n Used with \ref Camera.setCameraSettings(VIDEO_SETTINGS,int,int) "setCameraSettings()".\n Min/max range between max range defined in DTS.\n By default: [1 - 256]. \note Only available for ZED X/X Mini cameras.*/
        EXPOSURE_COMPENSATION, /**< Exposure-target compensation made after auto exposure.\n Reduces the overall illumination target by factor of F-stops.\n Affected value should be between 0 and 100 (mapped between [-2.0,2.0]).\n Default value is 50, i.e. no compensation applied. \note Only available for ZED X/X Mini cameras.*/
        DENOISING, /**< Level of denoising applied on both left and right images.\n Affected value should be between 0 and 100.\n Default value is 50. \note Only available for ZED X/X Mini cameras.*/
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    const int VIDEO_SETTINGS_VALUE_AUTO = -1;

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const VIDEO_SETTINGS &camSettings);

    inline ::std::ostream &operator<<(::std::ostream &os, const VIDEO_SETTINGS &camSettings) {
        return os << toString(camSettings);
    }
    ///@endcond

    /**
    \enum DEPTH_MODE
    \ingroup Depth_group
    \brief Lists available depth computation modes.
     */
    enum class DEPTH_MODE {
        NONE, /**< No depth map computation.\n Only rectified stereo images will be available.*/
        PERFORMANCE, /**< Computation mode optimized for speed.*/
        QUALITY, /**< Computation mode designed for challenging areas with untextured surfaces.*/
        ULTRA, /**< Computation mode that favors edges and sharpness.\n Requires more GPU memory and computation power.*/
        NEURAL, /**< End to End Neural disparity estimation.\n Requires AI module. */
        NEURAL_PLUS, /**< More accurate Neural disparity estimation.\n Requires AI module. */
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const DEPTH_MODE &depthMode);

    inline ::std::ostream &operator<<(::std::ostream &os, const DEPTH_MODE &depthMode) {
        return os << toString(depthMode);
    }
    ///@endcond

    /**
    \enum MEASURE
    \ingroup Depth_group
    \brief Lists retrievable measures.
     */
    enum class MEASURE {
        DISPARITY, /**< Disparity map. Each pixel contains 1 float.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C1"*/
        DEPTH, /**< Depth map in sl::UNIT defined in sl::InitParameters.coordinate_units. Each pixel contains 1 float.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C1".*/
        CONFIDENCE, /**< Certainty/confidence of the depth map. Each pixel contains 1 float.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C1"*/
        XYZ, /**< Point cloud. Each pixel contains 4 float (X, Y, Z, not used).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        XYZRGBA, /**< Colored point cloud. Each pixel contains 4 float (X, Y, Z, color).\n The color should to be read as an unsigned char[4] representing the RGBA color.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        XYZBGRA, /**< Colored point cloud. Each pixel contains 4 float (X, Y, Z, color).\n The color should to be read as an unsigned char[4] representing the BGRA color.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        XYZARGB, /**< Colored point cloud. Each pixel contains 4 float (X, Y, Z, color).\n The color should to be read as an unsigned char[4] representing the ARGB color.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        XYZABGR, /**< Colored point cloud. Each pixel contains 4 float (X, Y, Z, color).\n The color should to be read as an unsigned char[4] representing the ABGR color.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        NORMALS, /**< Normal vectors map. Each pixel contains 4 float (X, Y, Z, 0).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4".*/
        DISPARITY_RIGHT, /**< Disparity map for right sensor. Each pixel contains 1 float.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C1".*/
        DEPTH_RIGHT, /**< Depth map for right sensor. Each pixel contains 1 float.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C1".*/
        XYZ_RIGHT, /**< Point cloud for right sensor. Each pixel contains 4 float (X, Y, Z, not used).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        XYZRGBA_RIGHT, /**< Colored point cloud for right sensor. Each pixel contains 4 float (X, Y, Z, color).\n The color should to be read as an unsigned char[4] representing the RGBA color.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        XYZBGRA_RIGHT, /**< Colored point cloud for right sensor. Each pixel contains 4 float (X, Y, Z, color).\n The color should to be read as an unsigned char[4] representing the BGRA color.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        XYZARGB_RIGHT, /**< Colored point cloud for right sensor. Each pixel contains 4 float (X, Y, Z, color).\n The color should to be read as an unsigned char[4] representing the ARGB color.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        XYZABGR_RIGHT, /**< Colored point cloud for right sensor. Each pixel contains 4 float (X, Y, Z, color).\n The color should to be read as an unsigned char[4] representing the ABGR color.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4"*/
        NORMALS_RIGHT, /**< Normal vectors map for right view. Each pixel contains 4 float (X, Y, Z, 0).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::F32_C4".*/
        DEPTH_U16_MM, /**< Depth map in millimeter whatever the sl::UNIT defined in sl::InitParameters.coordinate_units.\n Invalid values are set to 0 and depth values are clamped at 65000.\n Each pixel contains 1 unsigned short.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U16_C1".*/
        DEPTH_U16_MM_RIGHT, /**< Depth map in millimeter for right sensor. Each pixel contains 1 unsigned short.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U16_C1".*/
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const MEASURE &measure);

    inline ::std::ostream &operator<<(::std::ostream &os, const MEASURE &measure) {
        return os << toString(measure);
    }
    ///@endcond

    /**
    \enum VIEW
    \ingroup Video_group
    \brief Lists available views.
     */
    enum class VIEW {
        LEFT, /**< Left BGRA image. Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" */
        RIGHT, /**< Right BGRA image. Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" */
        LEFT_GRAY, /**< Left gray image. Each pixel contains 1 unsigned char.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C1" */
        RIGHT_GRAY, /**< Right gray image. Each pixel contains 1 unsigned char.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C1" */
        LEFT_UNRECTIFIED, /**< Left BGRA unrectified image. Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" */
        RIGHT_UNRECTIFIED, /**< Right BGRA unrectified image. Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" */
        LEFT_UNRECTIFIED_GRAY, /**< Left gray unrectified image. Each pixel contains 1 unsigned char.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C1" */
        RIGHT_UNRECTIFIED_GRAY, /**< Right gray unrectified image. Each pixel contains 1 unsigned char.\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C1" */
        SIDE_BY_SIDE, /**< Left and right image (the image width is therefore doubled). Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" */
        DEPTH, /**< Color rendering of the depth. Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" \note Use \ref MEASURE "MEASURE::DEPTH" with \ref Camera.retrieveMeasure() to get depth values.*/
        CONFIDENCE, /**< Color rendering of the depth confidence. Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" \note Use \ref MEASURE "MEASURE::CONFIDENCE" with \ref Camera.retrieveMeasure() to get confidence values. */
        NORMALS, /**< Color rendering of the normals. Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" \note Use \ref MEASURE "MEASURE::NORMALS" with \ref Camera.retrieveMeasure() to get normal values. */
        DEPTH_RIGHT, /**< Color rendering of the right depth mapped on right sensor. Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" \note Use \ref MEASURE "MEASURE::DEPTH_RIGHT" with \ref Camera.retrieveMeasure() to get depth right values. */
        NORMALS_RIGHT, /**< Color rendering of the normals mapped on right sensor. Each pixel contains 4 unsigned char (B, G, R, A).\n Type: \ref MAT_TYPE "sl::MAT_TYPE::U8_C4" \note Use \ref MEASURE "MEASURE::NORMALS_RIGHT" with \ref Camera.retrieveMeasure() to get normal right values. */
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const VIEW &view);

    inline ::std::ostream &operator<<(::std::ostream &os, const VIEW &view) {
        return os << toString(view);
    }
    ///@endcond

    /**
    \enum TIME_REFERENCE
    \ingroup Video_group
    \brief Lists possible time references for timestamps or data.
     */
    enum class TIME_REFERENCE {
        IMAGE, /**< The requested timestamp or data will be at the time of the frame extraction. */
        CURRENT, /**< The requested timestamp or data will be at the time of the function call. */
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const TIME_REFERENCE &time_reference);

    inline ::std::ostream &operator<<(::std::ostream &os, const TIME_REFERENCE &time_reference) {
        return os << toString(time_reference);
    }
    ///@endcond

    /**
    \enum POSITIONAL_TRACKING_STATE
    \ingroup PositionalTracking_group
    \brief Lists the different states of positional tracking.
     */
    enum class POSITIONAL_TRACKING_STATE {
        SEARCHING, /**< \warn DEPRECATED: This state is no longer in use. */
        OK, /**< The positional tracking is functioning normally. */
        OFF, /**< The positional tracking is currently disabled. */
        FPS_TOO_LOW, /**< The effective FPS is too low to provide accurate motion tracking results. Consider adjusting performance parameters (e.g., depth mode, camera resolution) to improve tracking quality. */
        SEARCHING_FLOOR_PLANE, /**< The camera is currently searching for the floor plane to establish its position relative to it. The world reference frame will be set afterward. */
        UNAVAILABLE, /**< The tracking module was unable to perform tracking from the previous frame to the current frame. */
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const POSITIONAL_TRACKING_STATE &track_state);

    inline ::std::ostream &operator<<(::std::ostream &os, const POSITIONAL_TRACKING_STATE &track_state) {
        return os << toString(track_state);
    }
    ///@endcond

    /**
    \enum VISUAL_ODOMETRY_TRACKING_STATUS
    \ingroup PositionalTracking_group
    \brief Report the status of current odom tracking.
     */
    enum class ODOMETRY_STATUS {
        OK = 0, /**< The positional tracking module successfully tracked from the previous frame to the current frame. */
        UNAVAILABLE = 1, /**< The positional tracking module failed to track from the previous frame to the current frame. */
        LAST
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const ODOMETRY_STATUS &track_state);

    inline ::std::ostream &operator<<(::std::ostream &os, const ODOMETRY_STATUS &track_state) {
        return os << toString(track_state);
    }
    ///@endcond

    /**
    \enum SPATIAL_MEMORY_STATUS
    \ingroup PositionalTracking_group
    \brief Report the status of current map tracking.
     */
    enum class SPATIAL_MEMORY_STATUS {
        OK = 0, /**< The positional tracking module is operating normally. */
        LOOP_CLOSED = 1, /**< The positional tracking module detected a loop and corrected its position. */
        SEARCHING = 2, /**< The positional tracking module is searching for recognizable areas in the global map to relocate. */
        OFF = 3, /**< Spatial memory is disabled */
        LAST
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const SPATIAL_MEMORY_STATUS &track_state);

    inline ::std::ostream &operator<<(::std::ostream &os, const SPATIAL_MEMORY_STATUS &track_state) {
        return os << toString(track_state);
    }
    ///@endcond

    /**
    \enum POSITIONAL_TRACKING_FUSION_STATUS
    \ingroup PositionalTracking_group
    \brief Report the status of the positional tracking fusion.
     */
    enum class POSITIONAL_TRACKING_FUSION_STATUS {
        VISUAL_INERTIAL = 0,
        VISUAL = 1,
        INERTIAL = 2,
        GNSS = 3,
        VISUAL_INERTIAL_GNSS = 4,
        VISUAL_GNSS = 5,
        INERTIAL_GNSS = 6,
        UNAVAILABLE = 7,
        LAST
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const POSITIONAL_TRACKING_FUSION_STATUS &track_state);

    inline ::std::ostream &operator<<(::std::ostream &os, const POSITIONAL_TRACKING_FUSION_STATUS &track_state) {
        return os << toString(track_state);
    }
    ///@endcond

    /**
    \enum PositionalTrackingStatus
    \ingroup PositionalTracking_group
    \brief Lists the different status of positional tracking.
     */
    class PositionalTrackingStatus {
    public:
        /**
        @brief  Represents the current state of Visual-Inertial Odometry (VIO) tracking between the previous frame and the current frame.
         */
        ODOMETRY_STATUS odometry_status;

        /**
        @brief  Represents the current state of camera tracking in the global map.
         */
        SPATIAL_MEMORY_STATUS spatial_memory_status;

        /**
        @brief  Represents the current state of positional tracking fusion.
         */
        POSITIONAL_TRACKING_FUSION_STATUS tracking_fusion_status;
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const PositionalTrackingStatus &track_state);

    inline ::std::ostream &operator<<(::std::ostream &os, const PositionalTrackingStatus &track_state) {
        return os << toString(track_state);
    }
    ///@endcond

    /**
    \enum POSITIONAL_TRACKING_MODE
    \ingroup PositionalTracking_group
    \brief Lists the mode of positional tracking that can be used.
     */
    enum class POSITIONAL_TRACKING_MODE {
        GEN_1, /**< Default mode. Best compromise in performance. */
        GEN_2, /**< Next generation of positional tracking, allow better accuracy.*/
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const POSITIONAL_TRACKING_MODE& track_mode);

    inline ::std::ostream& operator<<(::std::ostream& os, const POSITIONAL_TRACKING_MODE& track_mode) {
        return os << toString(track_mode);
    }
    ///@endcond

    /**
    \enum AREA_EXPORTING_STATE
    \ingroup SpatialMapping_group
    \brief Lists the different states of spatial memory area export.
     */
    enum class AREA_EXPORTING_STATE {
        SUCCESS, /**< The spatial memory file has been successfully created.*/
        RUNNING, /**< The spatial memory is currently being written.*/
        NOT_STARTED, /**< The spatial memory file exportation has not been called.*/
        FILE_EMPTY, /**< The spatial memory contains no data, the file is empty.*/
        FILE_ERROR, /**< The spatial memory file has not been written because of a wrong file name.*/
        SPATIAL_MEMORY_DISABLED, /**< The spatial memory learning is disabled. No file can be created.*/
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const AREA_EXPORTING_STATE &area_export);

    inline ::std::ostream &operator<<(::std::ostream &os, const AREA_EXPORTING_STATE &area_export) {
        return os << toString(area_export);
    }
    ///@endcond

    /**
    \enum SPATIAL_MAPPING_STATE
    \ingroup SpatialMapping_group
    \brief Lists the different states of spatial mapping.
     */
    enum class SPATIAL_MAPPING_STATE {
        INITIALIZING, /**< The spatial mapping is initializing.*/
        OK, /**< The depth and tracking data were correctly integrated in the mapping algorithm.*/
        NOT_ENOUGH_MEMORY, /**< The maximum memory dedicated to the scanning has been reached.\n The mesh will no longer be updated.*/
        NOT_ENABLED, /**< sl::Camera::enableSpatialMapping() wasn't called or the scanning was stopped and not relaunched.*/
        FPS_TOO_LOW, /**< The effective FPS is too low to give proper results for spatial mapping.\n Consider using performance parameters (\ref DEPTH_MODE "sl::DEPTH_MODE::PERFORMANCE", \ref SpatialMappingParameters::MAPPING_RESOLUTION "sl::SpatialMappingParameters::MAPPING_RESOLUTION::LOW", low camera resolution (\ref RESOLUTION "sl::RESOLUTION::VGA/SVGA" or \ref RESOLUTION "sl::RESOLUTION::HD720").*/
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const SPATIAL_MAPPING_STATE &mapping_state);

    inline ::std::ostream &operator<<(::std::ostream &os, const SPATIAL_MAPPING_STATE &mapping_state) {
        return os << toString(mapping_state);
    }
    ///@endcond

    /**
    \enum REGION_OF_INTEREST_AUTO_DETECTION_STATE
    \ingroup Depth_group
    \brief Lists the different states of region of interest auto detection.
     */
    enum class REGION_OF_INTEREST_AUTO_DETECTION_STATE {
        RUNNING, /**< The region of interest auto detection is initializing.*/
        READY, /**< The region of interest mask is ready, if auto_apply was enabled, the region of interest mask is being used*/
        NOT_ENABLED, /**< The region of interest auto detection is not enabled*/
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String SL_SDK_EXPORT toString(const REGION_OF_INTEREST_AUTO_DETECTION_STATE &auto_roi_state);

    inline ::std::ostream &operator<<(::std::ostream &os, const REGION_OF_INTEREST_AUTO_DETECTION_STATE &auto_roi_state) {
        return os << toString(auto_roi_state);
    }
    ///@endcond

    /**
    \enum SVO_COMPRESSION_MODE
    \ingroup Video_group
    \brief Lists available compression modes for SVO recording.
    \note LOSSLESS is an improvement of previous lossless compression (used in ZED Explorer), even if size may be bigger, compression time is much faster.
     */
    enum class SVO_COMPRESSION_MODE {
        LOSSLESS, /**< PNG/ZSTD (lossless) CPU based compression.\n Average size: 42% of RAW*/
        H264, /**< H264 (AVCHD) GPU based compression.\n Average size: 1% of RAW \note Requires a NVIDIA GPU.*/
        H265, /**< H265 (HEVC) GPU based compression.\n Average size: 1% of RAW \note Requires a NVIDIA GPU.*/
        H264_LOSSLESS, /**< H264 Lossless GPU/Hardware based compression.\n Average size: 25% of RAW \n Provides a SSIM/PSNR result (vs RAW) >= 99.9%. \note Requires a NVIDIA GPU. */
        H265_LOSSLESS, /**< H265 Lossless GPU/Hardware based compression.\n Average size: 25% of RAW \n Provides a SSIM/PSNR result (vs RAW) >= 99.9%. \note Requires a NVIDIA GPU. */
        ///@cond SHOWHIDDEN
        LAST
        ///@endcond
    };

    ///@cond SHOWHIDDEN
    String /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ toString(const SVO_COMPRESSION_MODE &svo_compression);

    inline ::std::ostream &operator<<(::std::ostream &os, const SVO_COMPRESSION_MODE &svo_compression) {
        return os << toString(svo_compression);
    }
    ///@endcond

    /**
    \ingroup Video_group
    \brief Structure containing information about the status of the recording.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ RecordingStatus {
        /**
        \brief Report if the recording has been enabled.
         */
        bool is_recording;
        /**
        \brief Report if the recording has been paused.
         */
        bool is_paused;
        /**
        \brief Status of current frame.
        
        True for success or false if the frame could not be written in the SVO file.
         */
        bool status;
        /**
        \brief Compression time for the current frame in milliseconds.
         */
        double current_compression_time;
        /**
        \brief Compression ratio (% of raw size) for the current frame.
         */
        double current_compression_ratio;
        /**
        \brief Average compression time in milliseconds since beginning of recording.
         */
        double average_compression_time;
        /**
        \brief Average compression ratio (% of raw size) since beginning of recording.
         */
        double average_compression_ratio;

        /**
        \brief Default constructor. 
        
        Set all parameters to their default values.
         */
        RecordingStatus();
    };

};

#endif /*__DEFINES_HPP__*/
#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__


// Stereolabs namespace
namespace sl {

    ///@cond
    class SL_SDK_EXPORT Camera;
    ///@endcond

    /**
    \class InitParameters
    \ingroup Video_group
    \brief Class containing the options used to initialize the sl::Camera object.

    This class allows you to select multiple parameters for the sl::Camera such as the selected camera, resolution, depth mode, coordinate system, and units of measurement.
    \n Once filled with the desired options, it should be passed to the sl::Camera.open() method.

    \code
    #include <sl/Camera.hpp>

    using namespace sl;

    int main(int argc, char **argv) {
        Camera zed; // Create a ZED camera object

        InitParameters init_params; // Set initial parameters
        init_params.sdk_verbose = 0; // Disable verbose mode

        // Use the camera in LIVE mode
        init_params.camera_resolution = RESOLUTION::HD1080; // Use HD1080 video mode
        init_params.camera_fps = 30; // Set fps at 30

        // Or use the camera in SVO (offline) mode
        //init_params.input.setFromSVOFile("xxxx.svo");

        // Or use the camera in STREAM mode
        //init_params.input.setFromStream("192.168.1.12",30000);

        // Other parameters are left to their default values

        // Open the camera
        ERROR_CODE err = zed.open(init_params);
        if (err != ERROR_CODE::SUCCESS)
            exit(-1);

        // Close the camera
        zed.close();
        return 0;
    }
    \endcode

    With its default values, it opens the camera in live mode at \ref RESOLUTION "sl::RESOLUTION::HD720"
    (or \ref RESOLUTION "sl::RESOLUTION::HD1200" for the ZED X/X Mini) and sets the depth mode to \ref DEPTH_MODE "sl::DEPTH_MODE::ULTRA"
    (or \ref DEPTH_MODE "sl::DEPTH_MODE::PERFORMANCE" on Jetson).
    \n You can customize it to fit your application.
    \note The parameters can also be saved and reloaded using its \ref save() and \ref load() methods.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ InitParameters {
        friend class CameraMemberHandler;
        friend class Camera;
        ZED_SDK_VERSION_ATTRIBUTE
    public:

        /**
        \brief Desired camera resolution.
        \note Small resolutions offer higher framerate and lower computation time.
        \note In most situations, \ref RESOLUTION "sl::RESOLUTION::HD720" at 60 FPS is the best balance between image quality and framerate.
        
        Default: <ul>
        <li>ZED X/X Mini: \ref RESOLUTION "sl::RESOLUTION::HD1200"</li>
        <li>other cameras: \ref RESOLUTION "sl::RESOLUTION::HD720"</li></ul>
        \note Available resolutions are listed here: sl::RESOLUTION.
         */
        RESOLUTION camera_resolution;

        /**
        \brief Requested camera frame rate.
        
        If set to 0, the highest FPS of the specified \ref camera_resolution will be used.
        \n Default: 0
        \n\n See sl::RESOLUTION for a list of supported frame rates.
        \note If the requested \ref camera_fps is unsupported, the closest available FPS will be used.
         */
        int camera_fps;

        /**
        \brief Defines if a flip of the images is needed.
        
        If you are using the camera upside down, setting this parameter to \ref FLIP_MODE "sl::FLIP_MODE::ON" will cancel its rotation.
        \n The images will be horizontally flipped.
        \n Default: \ref FLIP_MODE "sl::FLIP_MODE::AUTO"
        \note From ZED SDK 3.2 a new sl::FLIP_MODE enum was introduced to add the automatic flip mode detection based on the IMU gravity detection.
        \note This does not work on \ref MODEL "sl::MODEL::ZED" cameras since they do not have the necessary sensors.
         */
        int camera_image_flip;

        /**
        \brief Disables the self-calibration process at camera opening.
        
        At initialization, sl::Camera runs a self-calibration process that corrects small offsets from the device's factory calibration.
        \n A drawback is that calibration parameters will slightly change from one (live) run to another, which can be an issue for repeatability.
        \n If set to true, self-calibration will be disabled and calibration parameters won't be optimized, raw calibration parameters from the configuration file will be used.
        \n Default: false
        \note In most situations, self calibration should remain enabled.
        \note You can also trigger the self-calibration at anytime after sl::Camera::open() by calling sl::Camera::updateSelfCalibration(), even if this parameter is set to true.
         */
        bool camera_disable_self_calib;

        /**
        \brief Enable the measurement computation on the right images.

        By default, the ZED SDK only computes a single depth map, aligned with the left camera image.
        \n This parameter allows you to enable \ref MEASURE "sl::MEASURE::DEPTH_RIGHT" and other \ref MEASURE "sl::MEASURE::XXX_RIGHT" at the cost of additional computation time.
        \n For example, mixed reality pass-through applications require one depth map per eye, so this parameter can be activated.
        \n Default: false
         */
        bool enable_right_side_measure;

        /**
        \brief Defines if sl::Camera object return the frame in real time mode.
        
        When playing back an SVO file, each call to sl::Camera::grab() will extract a new frame and use it.
        \n However, it ignores the real capture rate of the images saved in the SVO file.
        \n Enabling this parameter will bring the SDK closer to a real simulation when playing back a file by using the images' timestamps.
        \n Default: false
        \note sl::Camera::grab() will return an error when trying to play too fast, and frames will be dropped when playing too slowly.
         */
        bool svo_real_time_mode;

        /**
        \brief sl::DEPTH_MODE to be used.
        
        The ZED SDK offers several sl::DEPTH_MODE, offering various levels of performance and accuracy.
        \n This parameter allows you to set the sl::DEPTH_MODE that best matches your needs.
        \n Default: \ref DEPTH_MODE "sl::DEPTH_MODE::PERFORMANCE"
        \note Available depth mode are listed here: sl::DEPTH_MODE.
         */
        DEPTH_MODE depth_mode;

        /**
        \brief Defines whether the depth needs to be stabilized and to what extent.

        Regions of generated depth map can oscillate from one frame to another.
        \n These oscillations result from a lack of texture (too homogeneous) on an object and by image noise.
        \n This parameter controls a stabilization filter that reduces these oscillations.
        \n In the range [0-100]: <ul>
        <li>0 disable the depth stabilization (raw depth will be return)</li>
        <li>stabilization smoothness is linear from 1 to 100</li></ul>
        Default: 1
        
        \note The stabilization uses the positional tracking to increase its accuracy, 
        so the positional tracking module will be enabled automatically when set to a value different from 0.
        \note Note that calling sl::Camera::enablePositionalTracking() with your own parameters afterwards is still possible.
         */
        int depth_stabilization;

        /**
        \brief Minimum depth distance to be returned, measured in the sl::UNIT defined in \ref coordinate_units.
        
        This parameter allows you to specify the minimum depth value (from the camera) that will be computed.
        
        \n In stereovision (the depth technology used by the camera), looking for closer depth values can have a slight impact on performance and memory consumption.
        \n On most modern GPUs, performance impact will be low. However, the impact of memory footprint will be visible.
        \n In cases of limited computation power, increasing this value can provide better performance.
        \n Default: -1 (corresponding values are available <a href="https://www.stereolabs.com/docs/depth-sensing/depth-settings#depth-range">here</a>)

        \note \ref depth_minimum_distance value cannot be greater than 3 meters.
        \note 0 will imply that \ref depth_minimum_distance is set to the minimum depth possible for each camera
        (those values are available <a href="https://www.stereolabs.com/docs/depth-sensing/depth-settings#depth-range">here</a>).
         */
        float depth_minimum_distance;

        /**
        \brief Maximum depth distance to be returned, measured in the sl::UNIT defined in \ref coordinate_units.

        When estimating the depth, the ZED SDK uses this upper limit to turn higher values into sl::TOO_FAR ones.
        \note Changing this value has no impact on performance and doesn't affect the positional tracking nor the spatial mapping.
        \note It only change values the depth, point cloud and normals.
         */
        float depth_maximum_distance;

        /**
        \brief Unit of spatial data (depth, point cloud, tracking, mesh, etc.) for retrieval.
        
        Default: \ref UNIT "sl::UNIT::MILLIMETER"
         */
        UNIT coordinate_units;

        /**
        \brief sl::COORDINATE_SYSTEM to be used as reference for positional tracking, mesh, point clouds, etc.

        This parameter allows you to select the sl::COORDINATE_SYSTEM used by the sl::Camera object to return its measures.
        \n This defines the order and the direction of the axis of the coordinate system.
        \n Default: \ref COORDINATE_SYSTEM "sl::COORDINATE_SYSTEM::IMAGE"
         */
        COORDINATE_SYSTEM coordinate_system;

        /**
        \brief NVIDIA graphics card to use.
        
        By default the SDK will use the most powerful NVIDIA graphics card found.
        \n However, when running several applications, or using several cameras at the same time, splitting the load over available GPUs can be useful.
        \n This parameter allows you to select the GPU used by the sl::Camera using an ID from 0 to n-1 GPUs in your PC.
        \n Default: -1
        \note A non-positive value will search for all CUDA capable devices and select the most powerful.
         */
        CUdevice sdk_gpu_id;

        /**
        \brief Enable the ZED SDK verbose mode.
        
        This parameter allows you to enable the verbosity of the ZED SDK to get a variety of runtime information in the console.
        \n When developing an application, enabling verbose (<code>\ref sdk_verbose >= 1</code>) mode can help you understand the current ZED SDK behavior.
        \n However, this might not be desirable in a shipped version.
        \n Default: 1 (verbose message enabled)
        \note The verbose messages can also be exported into a log file.
        \note See \ref sdk_verbose_log_file for more.
         */
        int sdk_verbose;

        /**
        \brief File path to store the ZED SDK logs (if \ref sdk_verbose is enabled).

        The file will be created if it does not exist.
        \n Default: ""

        \note Setting this parameter to any value will redirect all standard output print calls of the entire program.
        \note This means that your own standard output print calls will be redirected to the log file.
        \note This parameter can be particularly useful for creating a log system, and with Unreal or Unity applications that don't provide a standard console output.
        \warning The log file won't be cleared after successive executions of the application.
        \warning This means that it can grow indefinitely if not cleared. 
         */
        String sdk_verbose_log_file;

        /**
        \brief CUcontext to be used.
        
        If your application uses another CUDA-capable library, giving its CUDA context to the ZED SDK can be useful when sharing GPU memories.
        \n This parameter allows you to set the CUDA context to be used by the ZED SDK.
        \n Leaving this parameter empty asks the SDK to create its own context.
        \n Default: (empty)

        \note When creating you own CUDA context, you have to define the device you will use. Do not forget to also specify it on \ref sdk_gpu_id.
        \note <b>On Jetson</b>, you have to set the flag CU_CTX_SCHED_YIELD, during CUDA context creation.
        \note You can also let the SDK create its own context, and use sl::Camera::getCUDAContext() to use it.
         */
        CUcontext sdk_cuda_ctx;

        /**
        \brief Defines the input source to initialize and open an sl::Camera object from.
        
        The SDK can handle different input types:
        - Select a camera by its ID (<i>/dev/videoX</i> on Linux, and 0 to N cameras connected on Windows)
        \code
        InitParameters init_params; // Set initial parameters
        init_params.sdk_verbose = 1; // Enable verbose mode
        init_params.input.setFromCameraID(0); // Selects the camera with ID = 0
        \endcode
        - Select a camera by its serial number
        \code
        InitParameters init_params; // Set initial parameters
        init_params.sdk_verbose = 1; // Enable verbose mode
        init_params.input.setFromSerialNumber(1010); // Selects the camera with serial number = 1010
        \endcode
        - Open a recorded sequence in the SVO file format
        \code
        InitParameters init_params; // Set initial parameters
        init_params.sdk_verbose = 1; // Enable verbose mode
        init_params.input.setFromSVOFile("/path/to/file.svo"); // Selects the and SVO file to be read
        \endcode
        - Open a streaming camera from its IP address and port
        \code
        InitParameters init_params; // Set initial parameters
        init_params.sdk_verbose = 1; // Enable verbose mode
        init_params.input.setFromStream("192.168.1.42"); // Selects the IP address of the streaming camera. A second optional parameter is available for port selection.
        \endcode

        \note Available cameras and their id/serial number can be listed using sl::Camera::getDeviceList() and sl::Camera::getStreamingDeviceList().
        \note Each sl::Camera will create its own memory (CPU and GPU),
        therefore the number of cameras used at the same time can be limited by the configuration of your computer (GPU/CPU memory and capabilities).
        
        Default : (empty)
        \note See sl::InputType for complementary information.
         */
        InputType input;

        /**
        \brief Optional path where the ZED SDK has to search for the settings file (<i>SN<XXXX>.conf</i> file).
        
        This file contains the calibration information of the camera.
        \n Default: ""
        
        \note The settings file will be searched in the default directory: <ul>
        <li><b>Linux</b>: <i>/usr/local/zed/settings/</i></li> 
        <li><b>Windows</b>: <i>C:/ProgramData/stereolabs/settings</i></li></ul>
        
        \note If a path is specified and no file has been found, the ZED SDK will search the settings file in the default directory.
        \note An automatic download of the settings file (through <b>ZED Explorer</b> or the installer) will still download the files on the default path.

        \code
        InitParameters init_params; // Set initial parameters
        std::string home = getenv("HOME"); // Get /home/user as string using getenv()
        std::string path = home + "/Documents/settings/"; // Assuming /home/<user>/Documents/settings/SNXXXX.conf exists. Otherwise, it will be searched in /usr/local/zed/settings/
        init_params.optional_settings_path = sl::String(path.c_str());
        \endcode
         */
        String optional_settings_path;

        /**
        \brief Optional path where the ZED SDK can find a file containing the calibration information of the camera computed by OpenCV.
        
        \note Using this will disable the factory calibration of the camera.
        \note The file must be in a XML/YAML/JSON formatting provided by OpenCV.
        \note It also must contain the following keys: Size, K_LEFT (intrinsic left), K_RIGHT (intrinsic right),
        D_LEFT (distortion left), D_RIGHT (distortion right), R (extrinsic rotation), T (extrinsic translation).
        \warning Erroneous calibration values can lead to poor accuracy in all ZED SDK modules.
         */
        String optional_opencv_calibration_file;

        /**
        \brief Requires the successful opening of the motion sensors before opening the camera.
        
        Default: false.

        \note If set to false, the ZED SDK will try to <b>open and use</b> the IMU (second USB device on USB2.0) and will open the camera successfully even if the sensors failed to open.
        
        This can be used for example when using a USB3.0 only extension cable (some fiber extension for example).
        \note This parameter only impacts the LIVE mode.
        \note If set to true, sl::Camera::open() will fail if the sensors cannot be opened.
        \note This parameter should be used when the IMU data must be available, such as object detection module or when the gravity is needed.
        
        \n\note This setting is not taken into account for \ref MODEL "sl::MODEL::ZED" camera since it does not include sensors.
         */
        bool sensors_required;

        /**
        \brief Enable the Enhanced Contrast Technology, to improve image quality.

        Default: true.
        
        \n If set to true, image enhancement will be activated in camera ISP. Otherwise, the image will not be enhanced by the IPS.
        \note This only works for firmware version starting from 1523 and up.
         */
        bool enable_image_enhancement;

        /**
        \brief Define a timeout in seconds after which an error is reported if the sl::Camera::open() method fails.

        Set to '-1' to try to open the camera endlessly without returning error in case of failure.
        \n Set to '0' to return error in case of failure at the first attempt.
        \n Default: 5.0
        \note This parameter only impacts the LIVE mode.
         */
        float open_timeout_sec;


        /**
        \brief Define the behavior of the automatic camera recovery during sl::Camera::grab() method call.
        
        When async is enabled and there's an issue with the communication with the sl::Camera object,
        sl::Camera::grab() will exit after a short period and return the \ref ERROR_CODE "sl::ERROR_CODE::CAMERA_REBOOTING" warning.
        \n The recovery will run in the background until the correct communication is restored.
        \n When \ref async_grab_camera_recovery is false, the sl::Camera::grab() method is blocking and will return
        only once the camera communication is restored or the timeout is reached. 
        \n Default: false
         */
        bool async_grab_camera_recovery;

        /**
        \brief Define a computation upper limit to the grab frequency.

        This can be useful to get a known constant fixed rate or limit the computation load while keeping a short exposure time by setting a high camera capture framerate.
        \n The value should be inferior to the sl::InitParameters.camera_fps and strictly positive.
        \note  It has no effect when reading an SVO file.
        
        This is an upper limit and won't make a difference if the computation is slower than the desired compute capping FPS.
        \note Internally the sl::Camera::grab() method always tries to get the latest available image while respecting the desired FPS as much as possible.
         */
        float grab_compute_capping_fps;


        /**
        \brief Enable or disable the image validity verification.

        This will perform additional verification on the image to identify corrupted data. This verification is done in the sl::Camera.grab() method and requires some computations.
        \n If an issue is found, the sl::Camera.grab() method will output a warning as [sl::ERROR_CODE::CORRUPTED_FRAME](\ref ERROR_CODE).
        \n This version doesn't detect frame tearing currently.
        \n Default: false (disabled)
         */
        bool enable_image_validity_check;


        /**
        \brief Default constructor.
        
        All the parameters are set to their default and optimized values.
         */
        InitParameters(RESOLUTION camera_resolution_ = RESOLUTION::AUTO,
                int camera_fps_ = 0,
                bool svo_real_time_mode_ = false,
#ifdef _SL_JETSON_
                DEPTH_MODE depth_mode_ = DEPTH_MODE::PERFORMANCE,
#else
                DEPTH_MODE depth_mode_ = DEPTH_MODE::ULTRA,
#endif
                UNIT coordinate_units_ = UNIT::MILLIMETER,
                COORDINATE_SYSTEM coordinate_system_ = COORDINATE_SYSTEM::IMAGE,
                int sdk_verbose_ = 1,
                int sdk_gpu_id_ = -1,
                float depth_minimum_distance_ = -1.,
                float depth_maximum_distance_ = -1.,
                bool camera_disable_self_calib_ = false,
                int camera_image_flip_ = FLIP_MODE::OFF,
                bool enable_right_side_measure_ = false,
                String sdk_verbose_log_file_ = String(),
                int depth_stabilization_ = 1,
                CUcontext sdk_cuda_ctx_ = CUcontext(),
                InputType input_type = InputType(),
                String optional_settings_path_ = String(),
                bool sensors_required_ = false,
                bool enable_image_enhancement_ = true,
                String optional_opencv_calibration_file_ = String(),
                float open_timeout_sec_ = 5.0f,
                bool async_grab_camera_recovery = false,
                float grab_compute_capping_fps = 0,
                bool enable_image_validity_check = false);

        /**
        \brief Saves the current set of parameters into a file to be reloaded with the \ref load() method.
        \param filename : Name of the file which will be created to store the parameters (extension '.yml' will be added if not set).
        \return True if file was successfully saved, otherwise false.
        \warning For security reason, the file must not exist.
        \warning In case a file already exists, the method will return false and existing file will not be updated.

        \code
        InitParameters init_params; // Set initial parameters
        init_params.sdk_verbose = 1; // Enable verbose mode
        init_params.input.setFromSVOFile("/path/to/file.svo"); // Selects the and SVO file to be read
        init_params.save("initParameters.yml"); // Export the parameters into a file
        \endcode
         */
        bool save(String filename);

        /**
        \brief Loads a set of parameters from the values contained in a previously \ref save() "saved" file.
        \param filename : Path to the file from which the parameters will be loaded  (extension '.yml' will be added at the end of the filename if not set).
        \return True if the file was successfully loaded, otherwise false.

        \code
        InitParameters init_params; // Set initial parameters
        init_params.load("initParameters.yml"); // Load the init_params from a previously exported file
        \endcode

        \note As the InitParameters files can be easily modified manually (using a text editor) this function allows you to test various settings without re-compiling your application.
         */
        bool load(String filename);


        /**
         * \brief Comparison operator ==
         * @param InitParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const InitParameters& param1) const;
        /**
         * \brief  Comparison operator !=
         * @param InitParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const InitParameters& param1) const;
    };


    /** @} */

    /**
    \ingroup Depth_group
    \brief Structure containing parameters that defines the behavior of sl::Camera::grab().
    
    The default constructor sets all parameters to their default settings.
    \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ RuntimeParameters {
        friend class CameraMemberHandler;
        friend class Camera;
        ZED_SDK_VERSION_ATTRIBUTE
    public:
        /**
        \brief Reference frame in which to provides the 3D measures (point cloud, normals, etc.).
        
        Default: \ref REFERENCE_FRAME "sl::REFERENCE_FRAME::CAMERA"
         */
        REFERENCE_FRAME measure3D_reference_frame;

        /**
        \brief Defines if the depth map should be computed.
        
        Default: true
        \note If set to false, only the images are available.
         */
        bool enable_depth;

        /**
        \brief Defines if the depth map should be completed or not.

        Default: false
        \note It is similar to the removed sl::SENSING_MODE::FILL.
        \warning Enabling this will override the confidence values \ref confidence_threshold and \ref texture_confidence_threshold as well as \ref remove_saturated_areas.
         */
        bool enable_fill_mode = false;

        /**
        \brief Threshold to reject depth values based on their confidence.
        
        Each depth pixel has a corresponding confidence (\ref MEASURE "sl::MEASURE::CONFIDENCE") in the range [1, 100].
        \n Decreasing this value will remove depth data from both objects edges and low textured areas, to keep only confident depth estimation data.
        \n Default: 95
        \note Pixels with a value close to 100 are not to be trusted. Accurate depth pixels tends to be closer to lower values.
        \note It can be seen as a probability of error, scaled to 100.
         */
        int confidence_threshold = 95;

        /**
        \brief Threshold to reject depth values based on their texture confidence.
        
        The texture confidence range is [1, 100].
        \n Decreasing this value will remove depth data from image areas which are uniform.
        \n Default: 100 (no depth pixel will be rejected)
        \note Pixels with a value close to 100 are not to be trusted. Accurate depth pixels tends to be closer to lower values.
         */
        int texture_confidence_threshold = 100;

        /**
        \brief Defines if the saturated area (luminance>=255) must be removed from depth map estimation.
        
        Default: true
        \note It is recommended to keep this parameter at true because saturated area can create false detection.
         */
        bool remove_saturated_areas = true;

        /**
        \brief Default constructor.
        
        All the parameters are set to their default values.
         */
        RuntimeParameters(bool enable_depth_ = true,
                bool enable_fill_mode_ = false,
                int confidence_threshold_ = 95,
                int texture_confidence_threshold_ = 100,
                REFERENCE_FRAME measure3D_reference_frame_ = REFERENCE_FRAME::CAMERA,
                bool remove_saturated_areas_ = true);

        /**
        \brief Saves the current set of parameters into a file to be reloaded with the \ref load() method.
        \param filename : Name of the file which will be created to store the parameters (extension '.yml' will be added if not set).
        \return True if the file was successfully saved, otherwise false.
        \warning For security reasons, the file must not already exist.
        \warning In case a file already exists, the method will return false and existing file will not be updated.
         */
        bool save(String filename);

        /**
        \brief Loads a set of parameters from the values contained in a previously \ref save() "saved" file.
        \param filename : Path to the file from which the parameters will be loaded (extension '.yml' will be added at the end of the filename if not detected).
        \return True if the file was successfully loaded, otherwise false.
         */
        bool load(String filename);

        /**
         * Comparison operator ==
         * @param RuntimeParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const RuntimeParameters& param1) const;
        /**
         * Comparison operator !=
         * @param RuntimeParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const RuntimeParameters& param1) const;
    };
    /** @} */

    /**
    \class PositionalTrackingParameters
    \ingroup PositionalTracking_group
    \brief Structure containing a set of parameters for the positional tracking module initialization.

    \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ PositionalTrackingParameters {
        friend class CameraMemberHandler;
        friend class Camera;

        ZED_SDK_VERSION_ATTRIBUTE
    public:

        /**
        \brief Position of the camera in the world frame when the camera is started.

        Use this sl::Transform to place the camera frame in the world frame.
        \n Default: Identity matrix.

        \note The camera frame (which defines the reference frame for the camera) is by default positioned at the world frame when tracking is started.
         */
        Transform initial_world_transform;

        /**
        \brief Whether the camera can remember its surroundings.

        This helps correct positional tracking drift and can be helpful for positioning different cameras relative to one other in space.
        \n Default: true

        \warning This mode requires more resources to run, but greatly improves tracking accuracy.
        \warning We recommend leaving it on by default.
         */
        bool enable_area_memory;

        /**
        \brief Whether to enable smooth pose correction for small drift correction.

        Default: false
         */
        bool enable_pose_smoothing;

        /**
        \brief Initializes the tracking to be aligned with the floor plane to better position the camera in space.

        Default: false
        \note This launches floor plane detection in the background until a suitable floor plane is found.
        \note The tracking will start in [sl::POSITIONAL_TRACKING_STATE::SEARCHING](\ref POSITIONAL_TRACKING_STATE) state.

        \warning This features does not work with [sl::MODEL::ZED](\ref MODEL) since it needs an IMU to classify the floor.
        \warning The camera needs to look at the floor during initialization for optimum results.
         */
        bool set_floor_as_origin;

        /**
        \brief Path of an area localization file that describes the surroundings (saved from a previous tracking session).

        Default: (empty)
        \note Loading an area file will start a search phase, during which the camera will try to position itself in the previously learned area.

        \warning The area file describes a specific location. If you are using an area file describing a different location, the tracking function will continuously search for a position and may not find a correct one.
        \warning The '.area' file can only be used with the same depth mode (sl::DEPTH_MODE) as the one used during area recording.
         */
        String area_file_path;

        /**
        \brief Whether to enable the IMU fusion.

        When set to false, only the optical odometry will be used.
        \n Default: true
        \note This setting has no impact on the tracking of a camera.
        \note [sl::MODEL::ZED](\ref MODEL) does not have an IMU.
         */
        bool enable_imu_fusion;

        /**
        \brief Whether to define the camera as static.

        If true, it will not move in the environment. This allows you to set its position using \ref initial_world_transform.
        \n All ZED SDK functionalities requiring positional tracking will be enabled without additional computation.
        \n sl::Camera::getPosition() will return the value set as \ref initial_world_transform.
        \n Default: false
         */
        bool set_as_static;

        /**
        \brief Minimum depth used by the ZED SDK for positional tracking.

        It may be useful for example if any steady objects are in front of the camera and may perturb the positional tracking algorithm.
        \n Default: -1 (no minimum depth)
         */
        float depth_min_range;

        /**
        \brief Whether to override 2 of the 3 rotations from \ref initial_world_transform using the IMU gravity.

        Default: true
        \note This parameter does nothing on [sl::ZED::MODEL](\ref MODEL) since it does not have an IMU.
         */
        bool set_gravity_as_origin;

        /**
        \brief Positional tracking mode used.

        Can be used to improve accuracy in some types of scene at the cost of longer runtime.
        \n Default: [sl::POSITIONAL_TRACKING_MODE::GEN_1](\ref POSITIONAL_TRACKING_MODE)
         */
        POSITIONAL_TRACKING_MODE mode;

        /**
        \brief Default constructor.
        
        Sets all parameters to their default and optimized values.
         */
        PositionalTrackingParameters(Transform init_position_ = Transform(),
                bool enable_memory_ = true,
                bool enable_pose_smoothing_ = false,
                String area_path_ = String(),
                bool set_floor_as_origin_ = false,
                bool enable_imu_fusion_ = true,
                bool set_as_static_ = false,
                float depth_min_range = -1.f,
                bool set_gravity_as_origin_ = true,
                POSITIONAL_TRACKING_MODE mode = POSITIONAL_TRACKING_MODE::GEN_1
                );

        /**
        \brief Saves the current set of parameters into a file to be reloaded with the \ref load() method.
        \param filename : Name of the file which will be created to store the parameters (extension '.yml' will be added if not set).
        \return True if the file was successfully saved, otherwise false.
        \warning For security reasons, the file must not already exist.
        \warning In case a file already exists, the method will return false and existing file will not be updated.
         */
        bool save(String filename);
        /**
        \brief Loads a set of parameters from the values contained in a previously \ref save() "saved" file.
        \param filename : Path to the file from which the parameters will be loaded (extension '.yml' will be added at the end of the filename if not detected).
        \return True if the file was successfully loaded, otherwise false.
         */
        bool load(String filename);

        /**
         * Comparison operator ==
         * @param PositionalTrackingParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const PositionalTrackingParameters& param1) const;
        /**
         * Comparison operator !=
         * @param PositionalTrackingParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const PositionalTrackingParameters& param1) const;
    };

    /**
    \class SpatialMappingParameters
    \ingroup SpatialMapping_group
    \brief Structure containing a set of parameters for the spatial mapping module.

    The default constructor sets all parameters to their default settings.
    \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ SpatialMappingParameters {
        friend class CameraMemberHandler;
        friend class Camera;
        ZED_SDK_VERSION_ATTRIBUTE
    public:
        /**
        \brief Float pair defining an interval.
         */
        typedef std::pair<float, float> interval;

        /**
        \enum SPATIAL_MAP_TYPE
        \ingroup SpatialMapping_group
        \brief Lists the types of spatial maps that can be created.
         */
        enum class SPATIAL_MAP_TYPE {
            MESH, /**< The geometry is represented by a set of vertices connected by edges and forming faces.\n No color information is available.*/
            FUSED_POINT_CLOUD, /**< The geometry is represented by a set of 3D colored points.*/
            ///@cond SHOWHIDDEN
            LAST
            ///@endcond
        };

        /**
        \enum MAPPING_RESOLUTION
        \ingroup SpatialMapping_group
        \brief Lists the spatial mapping resolution presets.
         */
        enum class MAPPING_RESOLUTION {
            HIGH, /**< Creates a detailed geometry.\n Requires lots of memory.*/
            MEDIUM, /**< Small variations in the geometry will disappear.\n Useful for big objects.*/
            LOW, /**< Keeps only huge variations of the geometry.\n Useful for outdoor purposes.*/
            ///@cond SHOWHIDDEN
            LAST
            ///@endcond
        };

        /**
        \enum MAPPING_RANGE
        \ingroup SpatialMapping_group
        \brief Lists the spatial mapping depth range presets.
         */
        enum class MAPPING_RANGE {
            SHORT, /**< Only depth close to the camera will be used during spatial mapping.*/
            MEDIUM, /**< Medium depth range.*/
            LONG, /**< Takes into account objects that are far.\n Useful for outdoor purposes.*/
            AUTO, /**< Depth range will be computed based on current sl::Camera state and parameters.*/
            ///@cond SHOWHIDDEN
            LAST
            ///@endcond
        };

        /**
        \brief Default constructor.
        
        Sets all parameters to their default and optimized values.
         */
        SpatialMappingParameters(MAPPING_RESOLUTION resolution = MAPPING_RESOLUTION::MEDIUM,
                MAPPING_RANGE range = MAPPING_RANGE::AUTO,
                int max_memory_usage_ = 2048,
                bool save_texture_ = false,
                bool use_chunk_only_ = false,
                bool reverse_vertex_order_ = false,
                SPATIAL_MAP_TYPE map_type = SPATIAL_MAP_TYPE::MESH,
                int stability_counter = 0);

        /**
        \brief Returns the value corresponding to a sl::SpatialMappingParameters::MAPPING_RESOLUTION preset in meters.
        \param mapping_resolution: The desired [MAPPING_RESOLUTION](\ref SpatialMappingParameters::MAPPING_RESOLUTION). Default: [MAPPING_RESOLUTION::MEDIUM](\ref SpatialMappingParameters::MAPPING_RESOLUTION)
        \return The value of \b mapping_resolution in meters.
         */
        static float get(MAPPING_RESOLUTION mapping_resolution = MAPPING_RESOLUTION::MEDIUM);

        /**
        \brief Sets the resolution to a sl::SpatialMappingParameters::MAPPING_RESOLUTION preset.
        \param mapping_resolution: The desired [MAPPING_RESOLUTION](\ref SpatialMappingParameters::MAPPING_RESOLUTION). Default: [MAPPING_RESOLUTION::MEDIUM](\ref SpatialMappingParameters::MAPPING_RESOLUTION)
         */
        void set(MAPPING_RESOLUTION mapping_resolution = MAPPING_RESOLUTION::MEDIUM);

        /**
        \brief Returns the value corresponding to a sl::SpatialMappingParameters::MAPPING_RANGE preset in meters.
        \param mapping_range: The desired [MAPPING_RANGE](\ref SpatialMappingParameters::MAPPING_RANGE). Default: [MAPPING_RANGE::MEDIUM](\ref SpatialMappingParameters::MAPPING_RANGE)
        \return The value of \b mapping_range in meters.
         */
        static float get(MAPPING_RANGE mapping_range = MAPPING_RANGE::MEDIUM);

        /**
        \brief Sets the range to a sl::SpatialMappingParameters::MAPPING_RANGE preset.
        \param mapping_range: The desired [MAPPING_RANGE](\ref SpatialMappingParameters::MAPPING_RANGE). Default: [MAPPING_RANGE::MEDIUM](\ref SpatialMappingParameters::MAPPING_RANGE)
         */
        void set(MAPPING_RANGE mapping_range = MAPPING_RANGE::MEDIUM);

        /**
        \brief Returns the recommended maximum depth value corresponding to a sl::SpatialMappingParameters::MAPPING_RESOLUTION preset.
        \param mapping_resolution: The desired [MAPPING_RESOLUTION](\ref SpatialMappingParameters::MAPPING_RESOLUTION).
        \param camera: The Camera object that will run the spatial mapping.
        \return The maximum value of the depth in meters.
         */
        static float getRecommendedRange(MAPPING_RESOLUTION mapping_resolution, Camera& camera);

        /**
        \brief Returns the recommended maximum depth value for the given resolution in meters.
        \param resolution_meters: The desired resolution in meters.
        \param camera: The Camera object that will run the spatial mapping.
        \return The maximum value of the depth in meters.
         */
        static float getRecommendedRange(float resolution_meters, Camera& camera);

        /**
        \brief Spatial mapping resolution in meters.
        \note It should fit \ref allowed_resolution.
         */
        float resolution_meter = 0.05f;

        /**
        \brief The resolution allowed by the spatial mapping:
        - \b allowed_resolution.first is the minimum value allowed
        - \b allowed_resolution.second is the maximum value allowed
         */
        static const interval allowed_resolution;

        /**
        \brief Depth range in meters.

        Can be different from the value set by sl::InitParameters::depth_maximum_distance.
        \note Set to 0 by default. In this case, the range is computed from \ref resolution_meter
        and from the current internal parameters to fit your application.
         */
        float range_meter = 0.f;

        /**
        \brief The maximum depth allowed by spatial mapping:
        - \b allowed_range.first is the minimum value allowed
        - \b allowed_range.second is the maximum value allowed
         */
        static const interval allowed_range;

        /**
        \brief Whether to save the texture.

        If set to true, you will be able to apply the texture to your mesh after it is created.
        \note This option will consume more memory.
        \note This option is only available for [sl::SpatialMappingParameters::SPATIAL_MAP_TYPE::MESH](\ref SpatialMappingParameters::SPATIAL_MAP_TYPE).
         */
        bool save_texture = false;

        /**
        \brief Whether to only use chunks.

        If set to false, you will ensure consistency between the mesh and its inner chunk data.
        \note Updating the mesh is time-consuming.
        \note Setting this to true results in better performance.
         */
        bool use_chunk_only = false;

        /**
        \brief The maximum CPU memory (in MB) allocated for the meshing process.
         */
        int max_memory_usage = 2048;

        /**
        \brief Whether to inverse the order of the vertices of the triangles.

        If your display process does not handle front and back face culling, you can use this to correct it.
        \note This option is only available for [sl::SpatialMappingParameters::SPATIAL_MAP_TYPE::MESH](\ref SpatialMappingParameters::SPATIAL_MAP_TYPE).
         */
        bool reverse_vertex_order = false;

        /**
        \brief The type of spatial map to be created.

        This dictates the format that will be used for the mapping (e.g. mesh, point cloud).
        \n See [sl::SpatialMappingParameters::SPATIAL_MAP_TYPE](\ref SpatialMappingParameters::SPATIAL_MAP_TYPE).
         */
        SPATIAL_MAP_TYPE map_type = SPATIAL_MAP_TYPE::MESH;

        /**
        \brief Control the integration rate of the current depth into the mapping process.

        This parameter controls how many times a stable 3D points should be seen before it is integrated into the spatial mapping.
        \n Default: 0 (this will define the stability counter based on the mesh resolution, the higher the resolution, the higher the stability counter)
         */
        int stability_counter = 0;

        /**
        \brief Saves the current set of parameters into a file to be reloaded with the \ref load() method.
        \param filename : Name of the file which will be created to store the parameters (extension '.yml' will be added if not set).
        \return True if the file was successfully saved, otherwise false.
        \warning For security reasons, the file must not already exist.
        \warning In case a file already exists, the method will return false and existing file will not be updated.
         */
        bool save(String filename);

        /**
        \brief Loads a set of parameters from the values contained in a previously \ref save() "saved" file.
        \param filename : Path to the file from which the parameters will be loaded (extension '.yml' will be added at the end of the filename if not detected).
        \return True if the file was successfully loaded, otherwise false.
         */
        bool load(String filename);

        /**
         * Comparison operator ==
         * @param SpatialMappingParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const SpatialMappingParameters& param1) const;
        /**
         * Comparison operator !=
         * @param SpatialMappingParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const SpatialMappingParameters& param1) const;
    };

    /**
    \ingroup Video_group
    \brief Structure containing the options used to stream with the ZED SDK.

    The default constructor sets all parameters to their default settings.

    \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/StreamingParameters {
        /**
        \brief Encoding used for streaming.
         */
        STREAMING_CODEC codec = STREAMING_CODEC::H265;

        /**
        \brief Port used for streaming.
        \warning Port must be an even number. Any odd number will be rejected.
        \warning Port must be opened.
         */
        unsigned short port = 30000;

        /**
        \brief Streaming bitrate (in Kbits/s) used for streaming.

        | sl::STREAMING_CODEC | sl::RESOLUTION | FPS   | Bitrate (kbps) |
        |---------------------|----------------|-------|----------------|
        | H264                |  HD2K          |   15  |     8500       |
        | H264                |  HD1080        |   30  |    12500       |
        | H264                |  HD720         |   60  |     7000       |
        | H265                |  HD2K          |   15  |     7000       |
        | H265                |  HD1080        |   30  |    11000       |
        | H265                |  HD720         |   60  |     6000       |

        Default: 0 (it will be set to the best value depending on your resolution/FPS)

        \note Available range: [1000 - 60000]
         */
        unsigned int bitrate = 0;

        /**
        \brief GOP size in number of frames.

        Default: -1 (the GOP size will last at maximum 2 seconds, depending on camera FPS)
        \note The GOP size determines the maximum distance between IDR/I-frames. Very high GOP size will result in slightly more efficient compression, especially on static scenes. But latency will increase.
        \note Maximum value: 256
         */
        int gop_size = -1;

        /**
        \brief Defines whether the adaptive bitrate is enable.

        Default: false
        \note Bitrate will be adjusted depending the number of packet dropped during streaming.
        \note If activated, the bitrate can vary between [bitrate/4, bitrate].
        \warning Currently, the adaptive bitrate only works when "sending" device is a NVIDIA Jetson (X1, X2, Xavier, Nano).
         */
        bool adaptative_bitrate = false;

        /**
        \brief Size of a single chunk.

        Default: 16084
        \note Stream buffers are divided into X number of chunks where each chunk is  \ref chunk_size bytes long.
        \note You can lower \ref chunk_size value if network generates a lot of packet lost: this will
        generates more chunk for a single image, but each chunk sent will be lighter to avoid inside-chunk corruption.
        \note Increasing this value can decrease latency.

        \n \note Available range: [1024 - 65000]
         */
        unsigned short chunk_size = 16084;


        /**
        \brief Framerate for the streaming output.

        Default: 0 (camera framerate will be taken)
        \warning This framerate must be below or equal to the camera framerate.
        \warning Allowed framerates are 15, 30, 60 or 100 if possible.
        \warning Any other values will be discarded and camera FPS will be taken.
         */
        unsigned int target_framerate = 0;


        /**
        \brief Default constructor.
        
        All the parameters are set to their default values.
         */
        StreamingParameters(STREAMING_CODEC codec_ = STREAMING_CODEC::H265,
                unsigned short port_ = 30000,
                unsigned int bitrate_ = 0,
                int gop_size_ = -1,
                bool adaptative_bitrate_ = false,
                unsigned short chunk_size_ = 16084,
                unsigned int target_framerate_ = 0
                );

        /**
         * Comparison operator ==
         * @param StreamingParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const StreamingParameters& param1) const;
        /**
         * Comparison operator !=
         * @param StreamingParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const StreamingParameters& param1) const;
    };

    /**
        \ingroup Video_group
        \brief Structure containing the options used to record.

        The default constructor sets all parameters to their default settings.
        
        \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/RecordingParameters {
        /**
        \brief Filename of the file to save the recording into.
         */
        String video_filename;

        /**
        \brief Compression mode the recording.

        Default: \ref SVO_COMPRESSION_MODE "sl::SVO_COMPRESSION_MODE::H264"
         */
        SVO_COMPRESSION_MODE compression_mode = SVO_COMPRESSION_MODE::H264;

        /**
        \brief Overrides the default bitrate of the SVO file, in kbits/s.
        
        Default: 0 (the default values associated with the resolution)
        \note Only works if \ref compression_mode is H264 or H265.
        \note Available range: 0 or [1000 - 60000]
         */
        unsigned int bitrate = 0;

        /**
        \brief Framerate for the recording file.

        Default: 0 (camera framerate will be taken)
        \warning This framerate must be below or equal to the camera framerate and camera framerate must be a multiple of the target framerate.
        \warning It means that it must respect <code> camera_framerate%target_framerate == 0</code>.
        \warning Allowed framerates are 15,30, 60 or 100 if possible.
        \warning Any other values will be discarded and camera FPS will be taken.
         */
        unsigned int target_framerate = 0;

        /**
        \brief Defines whether to decode and re-encode a streaming source.
        
        Default: false
        \note If set to false, it will avoid decoding/re-encoding and convert directly streaming input into a SVO file.
        \note This saves a encoding session and can be especially useful on NVIDIA Geforce cards where the number of encoding session is limited.
        \note \ref compression_mode, \ref target_framerate and \ref bitrate will be ignored in this mode.
         */
        bool transcode_streaming_input = false;

        /**
        \brief Default constructor.
        
        All the parameters are set to their default values.
         */
        RecordingParameters(String video_filename_ = "myRecording.svo2",
                SVO_COMPRESSION_MODE compression_mode_ = SVO_COMPRESSION_MODE::H264,
                unsigned int target_framerate_ = 0,
                unsigned int bitrate_ = 0,
                bool transcode_streaming_input_ = false);


        /**
         * Comparison operator ==
         * @param RecordingParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const RecordingParameters& param1) const;
        /**
         * Comparison operator !=
         * @param RecordingParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const RecordingParameters& param1) const;
    };

    /**
      \class BatchParameters
      \ingroup Object_group
      \brief Structure containing a set of parameters for batch object detection.

      The default constructor sets all parameters to their default settings.
      
      \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/ SL_SDK_EXPORT /*@endcond*/ BatchParameters {
        /**
        \brief Whether to enable the batch option in the object detection module.

        Batch queueing system provides:
        - deep-learning based re-identification
        - trajectory smoothing and filtering

        \note To activate this option, \ref enable must be set to true.
         */
        bool enable = false;

        /**
        \brief Max retention time in seconds of a detected object.

        After this time, the same object will mostly have a different id.
         */
        float id_retention_time = 240;

        /**
        \brief Trajectories will be output in batch with the desired latency in seconds.

        During this waiting time, re-identification of objects is done in the background.
        \note Specifying a short latency will limit the search (falling in timeout) for previously seen object ids but will be closer to real time output.
        \note Specifying a long latency will reduce the change of timeout in re-identification but increase difference with live output.
         */
        float latency = 2.f;

        /**
        \brief Default constructor.

        All the parameters are set to their default values.
         */
        BatchParameters(bool enable = false, float id_retention_time = 240.f,
                float batch_duration = 2.f);

        /**
         * Comparison operator ==
         * @param BatchParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const BatchParameters& param1) const;
        /**
         * Comparison operator !=
         * @param BatchParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const BatchParameters& param1) const;
    };

    /**
    \class ObjectDetectionParameters
    \ingroup Object_group
    \brief Structure containing a set of parameters for the object detection module.

    The default constructor sets all parameters to their default settings.

    \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ObjectDetectionParameters {
        /**
        \brief Id of the module instance.

        This is used to identify which object detection module instance is used.
         */
        unsigned int instance_module_id = 0;

        /**
        \brief Whether the object detection system includes object tracking capabilities across a sequence of images.
         */
        bool enable_tracking = true;

        /**
        \brief Whether the object masks will be computed.
         */
        bool enable_segmentation = false;

        /**
        \brief sl::OBJECT_DETECTION_MODEL to use.
         */
        OBJECT_DETECTION_MODEL detection_model = OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_FAST;

        /**
        \brief Upper depth range for detections.

        Default: -1.f (value set in sl::InitParameters.depth_maximum_distance)
        \note The value cannot be greater than sl::InitParameters.depth_maximum_distance and its unit is defined in sl::InitParameters.coordinate_units.
         */
        float max_range = -1.f;

        /**
        \brief Batching system parameters.

        Batching system (introduced in 3.5) performs short-term re-identification with deep-learning and trajectories filtering.
        \n sl::BatchParameters.enable must to be true to use this feature (by default disabled).
         */
        BatchParameters batch_parameters;

        /**
        \brief Filtering mode that should be applied to raw detections.

        Default: [sl::OBJECT_FILTERING_MODE::NMS_3D](\ref OBJECT_FILTERING_MODE) (same behavior as previous ZED SDK version)
        \note This parameter is only used in detection model [sl::OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_XXX](\ref OBJECT_DETECTION_MODEL)
        and [sl::OBJECT_DETECTION_MODEL::CUSTOM_BOX_OBJECTS](\ref OBJECT_DETECTION_MODEL).
        \note For custom object, it is recommended to use [sl::OBJECT_FILTERING_MODE::NMS_3D_PER_CLASS](\ref OBJECT_FILTERING_MODE)
        or [sl::OBJECT_FILTERING_MODE::NONE](\ref OBJECT_FILTERING_MODE).
        \note In this case, you might need to add your own NMS filter before ingesting the boxes into the object detection module.
         */
        OBJECT_FILTERING_MODE filtering_mode = OBJECT_FILTERING_MODE::NMS3D;

        /**
        \brief Prediction duration of the ZED SDK when an object is not detected anymore before switching its state to [sl::OBJECT_TRACKING_STATE::SEARCHING](\ref OBJECT_TRACKING_STATE).

        It prevents the jittering of the object state when there is a short misdetection.
        \n The user can define their own prediction time duration.
        \note During this time, the object will have [sl::OBJECT_TRACKING_STATE::OK](\ref OBJECT_TRACKING_STATE) state even if it is not detected.
        \note The duration is expressed in seconds.
        \warning \ref prediction_timeout_s will be clamped to 1 second as the prediction is getting worse with time.
        \warning Setting this parameter to 0 disables the ZED SDK predictions.
         */
        float prediction_timeout_s;

        /**
        \brief Whether to allow inference to run at a lower precision to improve runtime and memory usage.

        It might increase the initial optimization time and could include downloading calibration data or calibration cache and slightly reduce the accuracy.
        \note The fp16 is automatically enabled if the GPU is compatible and provides a speed up of almost x2 and reduce memory usage by almost half, no precision loss.
        \note This setting allow int8 precision which can speed up by another x2 factor (compared to fp16, or x4 compared to fp32) and half the fp16 memory usage, however some accuracy could be lost.
        \note The accuracy loss should not exceed 1-2% on the compatible models.
        \note The current compatible models are all [sl::AI_MODELS::HUMAN_BODY_XXXX](\ref AI_MODELS).
         */
        bool allow_reduced_precision_inference;


        /**
        \brief Default constructor.
        
        All the parameters are set to their default values.
         */
        ObjectDetectionParameters(bool enable_tracking_ = true,
                bool enable_segmentation_ = false,
                OBJECT_DETECTION_MODEL detection_model = OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_FAST,
                float max_range_ = -1.f,
                BatchParameters batch_trajectories_parameters = BatchParameters(),
                OBJECT_FILTERING_MODE filtering_mode_ = OBJECT_FILTERING_MODE::NMS3D,
                float prediction_timeout_s = 0.2f,
                bool allow_reduced_precision_inference = false
                , unsigned int instance_id = 0
                );

        /**
         * Comparison operator ==
         * @param ObjectDetectionParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const ObjectDetectionParameters& param1) const;
        /**
         * Comparison operator !=
         * @param ObjectDetectionParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const ObjectDetectionParameters& param1) const;


    };

    /**
    \class ObjectDetectionRuntimeParameters
    \ingroup Object_group
    \brief Structure containing a set of runtime parameters for the object detection module.

    The default constructor sets all parameters to their default settings.
    \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ObjectDetectionRuntimeParameters {
        /**
        \brief Confidence threshold.

        From 1 to 100, with 1 meaning a low threshold, more uncertain objects and 99 very few but very precise objects.
        \n Default: 20.f
        \note If the scene contains a lot of objects, increasing the confidence can slightly speed up the process, since every object instance is tracked.
        \note \ref detection_confidence_threshold is used as a fallback when sl::ObjectDetectionRuntimeParameters.object_class_detection_confidence_threshold is partially set.
         */
        float detection_confidence_threshold;

        /**
        \brief Defines which object types to detect and track.

        Default: {} (all classes are tracked)
        \note Fewer object types can slightly speed up the process since every object is tracked.
        \note Will output only the selected classes.

        In order to get all the available classes, the filter vector must be empty :
        \code
        object_class_filter = {};
        \endcode

        To select a set of specific object classes, like vehicles, persons and animals for instance:
        \code
        object_class_filter = {OBJECT_CLASS::VEHICLE, OBJECT_CLASS::PERSON, OBJECT_CLASS::ANIMAL};
        \endcode
         */
        std::vector<OBJECT_CLASS> object_class_filter;

        /**
        \brief Map of confidence thresholds for each class (can be empty for some classes).
        \note sl::ObjectDetectionRuntimeParameters.detection_confidence_threshold will be taken as fallback/default value.
         */
        std::map<OBJECT_CLASS, float> object_class_detection_confidence_threshold;

        /**
        \brief Default constructor.
        
        All the parameters are set to their default values.
         */
        ObjectDetectionRuntimeParameters(float detection_confidence_threshold = 20.f,
                std::vector<OBJECT_CLASS> object_class_filter = {},
        std::map<OBJECT_CLASS, float> object_class_detection_confidence_threshold = std::map<OBJECT_CLASS, float> ());

        /**
         * Comparison operator ==
         * @param ObjectDetectionRuntimeParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const ObjectDetectionRuntimeParameters& param1) const;
        /**
         * Comparison operator !=
         * @param ObjectDetectionRuntimeParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const ObjectDetectionRuntimeParameters& param1) const;

    };

    /**
    \ingroup Body_group
    \brief Structure containing a set of parameters for the body tracking module.

    The default constructor sets all parameters to their default settings.

    \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/BodyTrackingParameters {
        /**
        \brief Id of the module instance.

        This is used to identify which body tracking module instance is used.
         */
        unsigned int instance_module_id = 0;

        /**
        \brief Whether the body tracking system includes body/person tracking capabilities across a sequence of images.
         */
        bool enable_tracking = true;

        /**
        \brief Whether the body/person masks will be computed.
         */
        bool enable_segmentation = false;

        /**
        \brief sl::BODY_TRACKING_MODEL to use.
         */
        BODY_TRACKING_MODEL detection_model = BODY_TRACKING_MODEL::HUMAN_BODY_ACCURATE;

        /**
        \brief Whether to apply the body fitting.
         */
        bool enable_body_fitting = false;

        /**
        \brief Body format to be outputted by the ZED SDK with sl::Camera.retrieveBodies().
         */
        BODY_FORMAT body_format = BODY_FORMAT::BODY_18;

        /**
        \brief Selection of keypoints to outputted by the ZED SDK with sl::Camera.retrieveBodies().
         */
        BODY_KEYPOINTS_SELECTION body_selection = BODY_KEYPOINTS_SELECTION::FULL;

        /**
        \brief Upper depth range for detections.

        Default: -1.f (value set in sl::InitParameters.depth_maximum_distance)
        \note The value cannot be greater than sl::InitParameters.depth_maximum_distance and its unit is defined in sl::InitParameters.coordinate_units.
         */
        float max_range = -1.f;

        /**
        \brief Prediction duration of the ZED SDK when an object is not detected anymore before switching its state to [sl::OBJECT_TRACKING_STATE::SEARCHING](\ref OBJECT_TRACKING_STATE).

        It prevents the jittering of the object state when there is a short misdetection.
        \n The user can define their own prediction time duration.
        \note During this time, the object will have [sl::OBJECT_TRACKING_STATE::OK](\ref OBJECT_TRACKING_STATE) state even if it is not detected.
        \note The duration is expressed in seconds.
        \warning \ref prediction_timeout_s will be clamped to 1 second as the prediction is getting worse with time.
        \warning Setting this parameter to 0 disables the ZED SDK predictions.
         */
        float prediction_timeout_s;

        /**
        \brief Whether to allow inference to run at a lower precision to improve runtime and memory usage.

        It might increase the initial optimization time and could include downloading calibration data or calibration cache and slightly reduce the accuracy.
        \note The fp16 is automatically enabled if the GPU is compatible and provides a speed up of almost x2 and reduce memory usage by almost half, no precision loss.
        \note This setting allow int8 precision which can speed up by another x2 factor (compared to fp16, or x4 compared to fp32) and half the fp16 memory usage, however some accuracy could be lost.
        \note The accuracy loss should not exceed 1-2% on the compatible models.
        \note The current compatible models are all [sl::AI_MODELS::HUMAN_BODY_XXXX](\ref AI_MODELS).
         */
        bool allow_reduced_precision_inference;


        /**
        \brief Default constructor.

        All the parameters are set to their default values.
         */
        BodyTrackingParameters(bool enable_tracking_ = true,
                bool enable_segmentation_ = false,
                BODY_TRACKING_MODEL detection_model = BODY_TRACKING_MODEL::HUMAN_BODY_ACCURATE,
                bool enable_body_fitting_ = false,
                float max_range_ = -1.f,
                BODY_FORMAT body_format_ = BODY_FORMAT::BODY_18,
                BODY_KEYPOINTS_SELECTION body_selection = BODY_KEYPOINTS_SELECTION::FULL,
                float prediction_timeout_s = 0.2f,
#ifdef _SL_JETSON_
                bool allow_reduced_precision_inference = true
#else
                bool allow_reduced_precision_inference = false
#endif    
                , unsigned int instance_id = 0
                );

        /**
         * Comparison operator ==
         * @param BodyTrackingParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const BodyTrackingParameters& param1) const;
        /**
         * Comparison operator !=
         * @param BodyTrackingParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const BodyTrackingParameters& param1) const;


    };

    /**
    \ingroup Body_group
    
    \brief Structure containing a set of runtime parameters for the body tracking module.

    The default constructor sets all parameters to their default settings.
    \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/BodyTrackingRuntimeParameters {
        /**
        \brief Confidence threshold.

        From 1 to 100, with 1 meaning a low threshold, more uncertain objects and 99 very few but very precise objects.
        \n Default: 20.f
        \note If the scene contains a lot of objects, increasing the confidence can slightly speed up the process, since every object instance is tracked.
         */
        float detection_confidence_threshold;

        /**
        \brief Minimum threshold for the keypoints.

        The ZED SDK will only output the keypoints of the skeletons with threshold greater than this value.
        \n Default: 0
        \note It is useful, for example, to remove unstable fitting results when a skeleton is partially occluded.
         */
        int minimum_keypoints_threshold;

        /**
        \brief Control of the smoothing of the fitted fused skeleton.

        It is ranged from 0 (low smoothing) and 1 (high smoothing).
         */
        float skeleton_smoothing = 0.f;

        /**
        \brief Default constructor.

        All the parameters are set to their default values.
         */
        BodyTrackingRuntimeParameters(float detection_confidence_threshold = 20.f,
                int minimum_keypoints_threshold = 0, float skeleton_smoothing = 0.f);

        /**
         * Comparison operator ==
         * @param BodyTrackingRuntimeParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const BodyTrackingRuntimeParameters& param1) const;
        /**
         * Comparison operator !=
         * @param BodyTrackingRuntimeParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const BodyTrackingRuntimeParameters& param1) const;
    };

    /**
        \class PlaneDetectionParameters
        \ingroup SpatialMapping_group
        \brief Structure containing a set of parameters for the plane detection functionality.

        The default constructor sets all parameters to their default settings.
        \note Parameters can be adjusted by the user.
     */
    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ PlaneDetectionParameters {
        /**
         \brief Controls the spread of plane by checking the position difference.

         Default: 0.15 meters
         */
        float max_distance_threshold = 0.15f;

        /**
         \brief Controls the spread of plane by checking the angle difference.

         Default: 15 degrees
         */
        float normal_similarity_threshold = 15.f;

        /**
         * Comparison operator ==
         * @param PlaneDetectionParameters to compare
         * @return true if the two struct are identical
         */
        bool operator==(const PlaneDetectionParameters& param1) const;
        /**
         * Comparison operator !=
         * @param PlaneDetectionParameters to compare
         * @return true if the two struct are different
         */
        bool operator!=(const PlaneDetectionParameters& param1) const;
    };

    struct /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ RegionOfInterestParameters {
        /**
         \brief Filtering how far object in the ROI should be considered, this is useful for a vehicle for instance

         Default: 2.5 meters
         */
        float depth_far_threshold_meters = 2.5;

        /**
         \brief By default consider only the lower half of the image, can be useful to filter out the sky

         Default: 0.5, correspond to the lower half of the image
         */
        float image_height_ratio_cutoff = 0.5;

        /**
         \brief Once computed the ROI computed will be automatically applied

         Default: All modules
         */
        std::unordered_set<MODULE> auto_apply_module = {MODULE::ALL};
    };


    /*@cond SHOWHIDDEN*/
    class CameraMemberHandler;
    /*@endcond*/

    /**
    \class Camera
    \ingroup Video_group
    \brief This class serves as the primary interface between the camera and the various features provided by the SDK.
     
     It enables seamless integration and access to a wide array of capabilities, including video streaming, depth sensing, object tracking, mapping, and much more.
    
     A standard program will use the sl::Camera class like this:
     \code
     #include <sl/Camera.hpp>

     using namespace sl;

     int main(int argc, char **argv) {

             // --- Initialize a Camera object and open the ZED
             // Create a ZED camera object
             Camera zed;

             // Set configuration parameters
             InitParameters init_params;
             init_params.camera_resolution = RESOLUTION::HD720;         // Use HD720 video mode for USB cameras
             // init_params.camera_resolution = RESOLUTION::HD1200;     // Use HD1200 video mode for GMSL cameras
             init_params.camera_fps = 60;                               // Set fps at 60

             // Open the camera
             ERROR_CODE err = zed.open(init_params);
             if (err != ERROR_CODE::SUCCESS) {
                     std::cout << err << " exit program " << std::endl;
                     return -1;
             }

             // --- Main loop grabbing images and depth values
             // Capture 50 frames and stop
             int i = 0;
             Mat image, depth;
             while (i < 50) {
                     // Grab an image
                     if (zed.grab() == ERROR_CODE::SUCCESS) { // A new image is available if grab() returns SUCCESS

                             // Display a pixel color
                             zed.retrieveImage(image, VIEW::LEFT); // Get the left image
                             sl::uchar4 centerBGRA;
                             image.getValue<sl::uchar4>(image.getWidth() / 2, image.getHeight() / 2, &centerBGRA);
                             std::cout << "Image " << i << " center pixel B: " << (int)centerBGRA[0] << " G: " << (int)centerBGRA[1] << " R: " << (int)centerBGRA[2] << std::endl;

                             // Display a pixel depth
                             zed.retrieveMeasure(depth, MEASURE::DEPTH); // Get the depth map
                             float centerDepth;
                             depth.getValue<float>(depth.getWidth() / 2, depth.getHeight() / 2, &centerDepth);
                             std::cout << "Image " << i << " center depth: " << centerDepth << std::endl;

                             i++;
                     }
             }

             // --- Close the Camera
             zed.close();
             return 0;
     }
     \endcode
     *
     */
    class /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ Camera {
        friend CameraMemberHandler;
        friend SpatialMappingParameters;
        ZED_SDK_VERSION_ATTRIBUTE

    public:
        /**
        \brief Default constructor.
        
        Creates an empty Camera object.
        The parameters will be set when calling \ref open() "open(init_param)" with the desired InitParameters .

        A Camera object can be created like this:
        \code
        Camera zed;
        \endcode
        or
        \code
        Camera* zed = new Camera();
        \endcode
         */
        Camera();

        /**
        \brief Class destructor.
        
        The destructor will call the \ref close() function and clear the memory previously allocated by the object.
         */
        ~Camera();

        /**
        \brief Opens the ZED camera from the provided InitParameters.

        The method will also check the hardware requirements and run a self-calibration.

        \param init_parameters : A structure containing all the initial parameters. Default: a preset of InitParameters.
        \return An error code giving information about the internal process. If \ref ERROR_CODE "ERROR_CODE::SUCCESS" is returned, the camera is ready to use. Every other code indicates an error and the program should be stopped.

        Here is the proper way to call this function:
        \code
        Camera zed; // Create a ZED camera object

        InitParameters init_params; // Set configuration parameters
        init_params.camera_resolution = RESOLUTION::HD720; // Use HD720 video mode
        init_params.camera_fps = 60; // Set fps at 60

        // Open the camera
        ERROR_CODE err = zed.open(init_params);
        if (err != ERROR_CODE::SUCCESS) {
                std::cout << toString(err) << std::endl; // Display the error
                exit(-1);
        }
        \endcode

        \note If you are having issues opening a camera, the diagnostic tool provided in the SDK can help you identify to problems.
                - <b>Windows:</b> <i>C:\\Program Files (x86)\\ZED SDK\\tools\\ZED Diagnostic.exe</i>
                - <b>Linux:</b> <i>/usr/local/zed/tools/ZED Diagnostic</i>
        \note If this method is called on an already opened camera, \ref close() will be called.
         */
        ERROR_CODE open(InitParameters init_parameters = InitParameters());


        /**
        \brief Returns the InitParameters used.

        It corresponds to the structure given as argument to the \ref open() method.

        \return InitParameters containing the parameters used to initialize the Camera object.
         */
        InitParameters getInitParameters();

        /**
        \brief Reports if the camera has been successfully opened.

        It has the same behavior as checking if \ref open() returns \ref ERROR_CODE "ERROR_CODE::SUCCESS".
        \return true if the ZED camera is already setup, otherwise false.
         */
        inline bool isOpened() {
            return opened;
        }

        /**
        \brief Close an opened camera.

        If \ref open() has been called, this method will close the connection to the camera (or the SVO file) and free the corresponding memory.

        If \ref open() wasn't called or failed, this method won't have any effects.

        \note If an asynchronous task is running within the \ref Camera object, like \ref saveAreaMap(), this method will wait for its completion.
        \note To apply a new \ref InitParameters, you will need to close the camera first and then open it again with the new InitParameters values.

        \warning If the CUDA context was created by \ref open(), this method will destroy it.
        \warning Therefore you need to make sure to delete your GPU \ref sl::Mat objects before the context is destroyed.
         */
        void close();


        /**
        \brief This method will grab the latest images from the camera, rectify them, and compute the \ref retrieveMeasure() "measurements" based on the \ref RuntimeParameters provided (depth, point cloud, tracking, etc.)
        
        As measures are created in this method, its execution can last a few milliseconds, depending on your parameters and your hardware.
        \n The exact duration will mostly depend on the following parameters:
           - \ref InitParameters.enable_right_side_measure : Activating this parameter increases computation time.
           - \ref InitParameters.camera_resolution : Lower resolutions are faster to compute.
           - \ref enablePositionalTracking() : Activating the tracking is an additional load.
           - \ref RuntimeParameters.enable_depth : Avoiding the depth computation must be faster. However, it is required by most SDK features (tracking, spatial mapping, plane estimation, etc.)
           - \ref InitParameters.depth_mode : \ref DEPTH_MODE "DEPTH_MODE::PERFORMANCE" will run faster than \ref DEPTH_MODE "DEPTH_MODE::ULTRA".
           - \ref InitParameters.depth_stabilization : Stabilizing the depth requires an additional computation load as it enables tracking.

        This method is meant to be called frequently in the main loop of your application.

        \note Since ZED SDK 3.0, this method is blocking. It means that grab() will wait until a new frame is detected and available.
        \note If no new frames is available until timeout is reached, grab() will return \ref ERROR_CODE "ERROR_CODE::CAMERA_NOT_DETECTED" since the camera has probably been disconnected.

        \param rt_parameters : A structure containing all the runtime parameters. Default: a preset of \ref RuntimeParameters.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" means that no problem was encountered.
        \note Returned errors can be displayed using toString().

        \code
        // Set runtime parameters after opening the camera
        RuntimeParameters runtime_param;
        runtime_param.confidence_threshold = 50; // Change the confidence threshold

        Mat image;
        while (true) {
            // Grab an image
            if (zed.grab(runtime_param) == ERROR_CODE::SUCCESS) { // A new image is available if grab() returns SUCCESS
                zed.retrieveImage(image, VIEW::LEFT); // Get the left image
                // Use the image for your application
            }
        }
        \endcode
         */
        ERROR_CODE grab(RuntimeParameters rt_parameters = RuntimeParameters());


        /**
        \brief Returns the RuntimeParameters used.
        
        It corresponds to the structure given as argument to the \ref grab() method.

        \return \ref RuntimeParameters containing the parameters that define the behavior of the \ref grab method.
         */
        RuntimeParameters getRuntimeParameters();


        /**
        \brief Returns the CameraInformation associated the camera being used.

        To ensure accurate calibration, it is possible to specify a custom resolution as a parameter when obtaining scaled information, as calibration parameters are resolution-dependent.
        \n When reading an SVO file, the parameters will correspond to the camera used for recording.

        \param image_size : You can specify a size different from the default image size to get the scaled camera information. Default = (0,0) meaning original image size (given by \ref CameraConfiguration.resolution "getCameraInformation().camera_configuration.resolution").
        \return \ref CameraInformation containing the calibration parameters of the ZED, as well as serial number and firmware version.

        \note The \ref CameraConfiguration "CameraInformation.camera_configuration" will contain two types of calibration parameters:
        - \ref CameraConfiguration.calibration_parameters "camera_configuration.calibration_parameters": it contains the calibration for the <b>rectified</b> images.
        Rectified images are images that would come from perfect stereo camera (exact same camera, perfectly matched).
        Therefore, the camera matrix will be identical for left and right camera, and the distortion/rotation/translation matrix will be null (except for Tx, which is the exact distance between both eyes).
        - \ref CameraConfiguration.calibration_parameters_raw "camera_configuration.calibration_parameters_raw": it contains the original calibration before rectification. Therefore it should be identical or very close to the calibration file SNXXXX.conf where XXXX is the serial number of the camera.

        \warning The returned parameters might vary between two execution due to the \ref InitParameters.camera_disable_self_calib "self-calibration" being run in the \ref open() method.
        \note The calibration file SNXXXX.conf can be found in:
        - <b>Windows:</b> <i>C:/ProgramData/Stereolabs/settings/</i>
        - <b>Linux:</b> <i>/usr/local/zed/settings/</i>
         */
        CameraInformation getCameraInformation(Resolution image_size = Resolution(0, 0));

        /**
        \brief Perform a new self-calibration process.

        In some cases, due to temperature changes or strong vibrations, the stereo calibration becomes less accurate.
        \n Use this method to update the self-calibration data and get more reliable depth values.
        \note The self calibration will occur at the next \ref grab() call.
        \note This method is similar to the previous resetSelfCalibration() used in 2.X SDK versions.
        \warning New values will then be available in \ref getCameraInformation(), be sure to get them to still have consistent 2D <-> 3D conversion.
         */
        void updateSelfCalibration();

        /**
        \brief Gets the Camera-created CUDA context for sharing it with other CUDA-capable libraries.
        
        This can be useful for sharing GPU memories.
        \note If you're looking for the opposite mechanism, where an existing CUDA context is given to the \ref Camera, please check \ref InitParameters.sdk_cuda_ctx
        \return The CUDA context used for GPU calls.
         */
        CUcontext getCUDAContext();

        /**
        \brief Gets the Camera-created CUDA stream for sharing it with other CUDA-capable libraries.
        \return The CUDA stream used for GPU calls.
         */
        CUstream getCUDAStream();

        ///@{
        /// @name Video
        // -----------------------------------------------------------------
        //                         Video :
        // -----------------------------------------------------------------

        /**
        \brief Retrieves images from the camera (or SVO file).

        Multiple images are available along with a view of various measures for display purposes.
        \n Available images and views are listed \ref VIEW "here".
        \n As an example, \ref VIEW "VIEW::DEPTH" can be used to get a gray-scale version of the depth map, but the actual depth values can be retrieved using \ref retrieveMeasure().
        \n
        \n <b>Pixels</b>
        \n Most VIEW modes output image with 4 channels as BGRA (Blue, Green, Red, Alpha), for more information see enum \ref VIEW
        \n
        \n <b>Memory</b>
        \n By default, images are copied from GPU memory to CPU memory (RAM) when this function is called.
        \n If your application can use GPU images, using the <b>type</b> parameter can increase performance by avoiding this copy.
        \n If the provided \ref Mat object is already allocated  and matches the requested image format, memory won't be re-allocated.
        \n
        \n <b>Image size</b>
        \n By default, images are returned in the resolution provided by \ref Resolution "getCameraInformation().camera_configuration.resolution".
        \n However, you can request custom resolutions. For example, requesting a smaller image can help you speed up your application.

        \warning A sl::Mat resolution higher than the camera resolution <b>cannot</b> be requested.

        \param mat  : The \ref sl::Mat to store the image. The method will create the Mat if necessary at the proper resolution. If already created, it will just update its data (CPU or GPU depending on the MEM type).
        \param view : Defines the image you want (see \ref VIEW). Default : \ref VIEW "VIEW::LEFT".
        \param type : Defines on which memory the image should be allocated. Default: \ref MEM "MEM::CPU".
        \param image_size : If specified, define the resolution of the output sl::Mat. If set to \ref Resolution "Resolution(0,0)", the camera resolution will be taken. Default: (0,0).
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the method succeeded.
        \return \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_PARAMETERS" if the view mode requires a module not enabled (\ref VIEW "VIEW::DEPTH" with \ref DEPTH_MODE "DEPTH_MODE::NONE" for example).
        \return \ref ERROR_CODE "ERROR_CODE::INVALID_RESOLUTION" if the resolution is higher than one provided by \ref Resolution "getCameraInformation().camera_configuration.resolution".
        \return \ref ERROR_CODE "ERROR_CODE::FAILURE" if another error occurred.

        \note As this method retrieves the images grabbed by the \ref grab() method, it should be called afterward.

        \code
        Mat leftImage; //create sl::Mat objects to store the image
        while (true) {
                // Grab an image
                if (zed.grab() == ERROR_CODE::SUCCESS) { // A new image is available if grab() returns SUCCESS
                        zed.retrieveImage(leftImage, VIEW::LEFT); // Get the rectified left image

                        // Display the center pixel colors
                        sl::uchar4 leftCenter;
                        leftImage.getValue<sl::uchar4>(leftImage.getWidth() / 2, leftImage.getHeight() / 2, &leftCenter);
                        std::cout << "left image color B: " << (int)leftCenter[0] << " G: " << (int)leftCenter[1] << " R: " << (int)leftCenter[2] << std::endl;
                }
        }
        \endcode
         */
        ERROR_CODE retrieveImage(Mat& mat, VIEW view = VIEW::LEFT, MEM type = MEM::CPU, Resolution image_size = Resolution(0, 0));

        /**
        \brief Returns the current value of the requested \ref VIDEO_SETTINGS "camera setting" (gain, brightness, hue, exposure, etc.).

        Possible values (range) of each setting are available \ref VIDEO_SETTINGS "here".

        \param settings : The requested setting.
        \param setting : The setting variable to fill.
        \return \ref ERROR_CODE to indicate if the method was successful. If successful, setting will be filled with the corresponding value.

        \code
        int gain;
        err = zed.getCameraSettings(VIDEO_SETTINGS::GAIN, gain);
        if (err == ERROR_CODE::SUCCESS)
            std::cout << "Current gain value: " << gain << std::endl;
        \endcode

        \note The method works only if the camera is open in LIVE or STREAM mode.
        \note Settings are not exported in the SVO file format.
         */
        ERROR_CODE getCameraSettings(VIDEO_SETTINGS settings, int& setting);

        /**
        \brief Fills the current values of the requested \ref VIDEO_SETTINGS "settings" for \ref VIDEO_SETTINGS that supports two values (min/max).
        
        This method only works with the following VIDEO_SETTINGS:
                - \ref VIDEO_SETTINGS "sl::VIDEO_SETTINGS::AUTO_EXPOSURE_TIME_RANGE"
                - \ref VIDEO_SETTINGS "sl::VIDEO_SETTINGS::AUTO_ANALOG_GAIN_RANGE"
                - \ref VIDEO_SETTINGS "sl::VIDEO_SETTINGS::AUTO_DIGITAL_GAIN_RANGE"
        
        Possible values (range) of each setting are available \ref VIDEO_SETTINGS "here".

        \param settings : The requested setting.
        \param min_val : The setting minimum variable to fill.
        \param max_val : The setting maximum variable to fill.
        \return \ref ERROR_CODE to indicate if the method was successful. If successful, setting will be filled with the corresponding value.

        \code
        int aec_range_min = 0;
        int aec_range_max = 0;
        sl::ERROR_CODE err = zed.getCameraSettings(sl::VIDEO_SETTINGS::AUTO_EXPOSURE_TIME_RANGE, aec_range_min, aec_range_max);
        std::cout << "Current AUTO_EXPOSURE_TIME_RANGE range values ==> min: " << aec_range_min << " max: " << aec_range_max << std::endl;
        \endcode

        \note Works only with ZED X that supports low-level controls
         */
        ERROR_CODE getCameraSettings(VIDEO_SETTINGS settings, int& min_val, int& max_val);


        /**
        \brief Overloaded method for \ref VIDEO_SETTINGS "VIDEO_SETTINGS::AEC_AGC_ROI" which takes a Rect as parameter.

        \param setting : Must be set at \ref VIDEO_SETTINGS "VIDEO_SETTINGS::AEC_AGC_ROI", otherwise the method will have no impact.
        \param roi : Roi that will be filled.
        \param side : \ref SIDE on which to get the ROI from.
        \return \ref ERROR_CODE to indicate if the method was successful. If successful, roi will be filled with the corresponding values.

        \note Works only if the camera is open in LIVE or STREAM mode with \ref VIDEO_SETTINGS "VIDEO_SETTINGS::AEC_AGC_ROI".
        \note It will return \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_CALL" or \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_PARAMETERS" otherwise.
         */
        ERROR_CODE getCameraSettings(VIDEO_SETTINGS settings, Rect& roi, sl::SIDE side = sl::SIDE::BOTH);

        /**
        \brief Sets the value of the requested \ref VIDEO_SETTINGS "camera setting" (gain, brightness, hue, exposure, etc.).

        This method only applies for \ref VIDEO_SETTINGS that require a single value.

        Possible values (range) of each setting are available \ref VIDEO_SETTINGS "here".

        \param settings : The setting to be set.
        \param value : The value to set. Default: auto mode
        \return \ref ERROR_CODE to indicate if the method was successful.

        \warning Setting \ref VIDEO_SETTINGS "VIDEO_SETTINGS::EXPOSURE" or \ref VIDEO_SETTINGS "VIDEO_SETTINGS::GAIN" to default will automatically sets the other to default.

        \note The method works only if the camera is open in LIVE or STREAM mode.

        \code
        // Set the gain to 50
        zed.setCameraSettings(VIDEO_SETTINGS::GAIN, 50);
        \endcode
         */
        ERROR_CODE setCameraSettings(VIDEO_SETTINGS settings, int value = VIDEO_SETTINGS_VALUE_AUTO);

        /**
        \brief Sets the value of the requested \ref VIDEO_SETTINGS "camera setting" that supports two values (min/max).

        This method only works with the following VIDEO_SETTINGS:
        - \ref VIDEO_SETTINGS "VIDEO_SETTINGS::AUTO_EXPOSURE_TIME_RANGE"
        - \ref VIDEO_SETTINGS "VIDEO_SETTINGS::AUTO_ANALOG_GAIN_RANGE"
        - \ref VIDEO_SETTINGS "VIDEO_SETTINGS::AUTO_DIGITAL_GAIN_RANGE"
        
        Possible values (range) of each setting are available \ref VIDEO_SETTINGS "here".

        \param settings : The setting to be set.
        \param min : The minimum value that can be reached (-1 or 0 gives full range).
        \param max : The maximum value that can be reached (-1 or 0 gives full range).
        \return \ref ERROR_CODE to indicate if the method was successful.

        \warning If \ref VIDEO_SETTINGS settings is not supported or min >= max, it will return \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_PARAMETERS".
        \note The method works only if the camera is open in LIVE or STREAM mode.

        \code
        // For ZED X based product, set the automatic exposure from 2ms to 5ms. Expected exposure time cannot go beyond those values
        zed.setCameraSettings(VIDEO_SETTINGS::AUTO_EXPOSURE_TIME_RANGE, 2000, 5000);
        \endcode
         */
        ERROR_CODE setCameraSettings(VIDEO_SETTINGS settings, int min, int max);

        /**
        \brief Overloaded method for \ref VIDEO_SETTINGS "VIDEO_SETTINGS::AEC_AGC_ROI" which takes a Rect as parameter.

        \param setting : Must be set at \ref VIDEO_SETTINGS "VIDEO_SETTINGS::AEC_AGC_ROI", otherwise the method will have no impact.
        \param roi : Rect that defines the target to be applied for AEC/AGC computation. Must be given according to camera resolution.
        \param side : \ref SIDE on which to be applied for AEC/AGC computation.
        \param reset : Cancel the manual ROI and reset it to the full image.

        \note Works only if the camera is open in LIVE or STREAM mode with \ref VIDEO_SETTINGS "VIDEO_SETTINGS::AEC_AGC_ROI".
        \return \ref ERROR_CODE to indicate if the method was successful.
         */
        ERROR_CODE setCameraSettings(VIDEO_SETTINGS settings, Rect roi, sl::SIDE side = sl::SIDE::BOTH, bool reset = false);


        /**
        \brief Get the range for the specified camera settings \ref VIDEO_SETTINGS as min/max value.

        \param setting : Must be set at a valid \ref VIDEO_SETTINGS that accepts a min/max range and available for the current camera model.
        \return \ref ERROR_CODE to indicate if the method was successful.
         */
        ERROR_CODE getCameraSettingsRange(VIDEO_SETTINGS settings, int& min, int& max);


        /**
        \brief Test if the video setting is supported by the camera

        \param setting : The video setting to test
        \return true if the \ref VIDEO_SETTINGS is supported by the camera, false otherwise
         */
        bool isCameraSettingSupported(VIDEO_SETTINGS setting);

        /**
        \brief Returns the current framerate at which the \ref grab() method is successfully called.

        The returned value is based on the difference of camera \ref getTimestamp() "timestamps" between two successful grab() calls.
        \return The current SDK framerate.
        \warning The returned framerate (number of images grabbed per second) can be lower than \ref InitParameters.camera_fps if the \ref grab() function runs slower than the image stream or is called too often.

        \code
        int current_fps = zed.getCurrentFPS();
        std::cout << "Current framerate: " << current_fps << std::endl;
        \endcode
         */
        float getCurrentFPS();

        /**
        \brief Returns the timestamp in the requested \ref TIME_REFERENCE.

        - When requesting the \ref TIME_REFERENCE "TIME_REFERENCE::IMAGE" timestamp, the UNIX nanosecond timestamp of the latest \ref grab() "grabbed" image will be returned.
        \n This value corresponds to the time at which the entire image was available in the PC memory. As such, it ignores the communication time that corresponds to 1 or 2 frame-time based on the fps (ex: 16.6ms to 33ms at 60fps).

        - When requesting the \ref TIME_REFERENCE "TIME_REFERENCE::CURRENT" timestamp, the current UNIX nanosecond timestamp is returned.

        \n This function can also be used when playing back an SVO file.

        \param reference_time : The selected \ref TIME_REFERENCE.

        \return The timestamp in nanosecond. 0 if not available (SVO file without compression).

        \note As this function returns UNIX timestamps, the reference it uses is common across several \ref Camera instances.
        \n This can help to organized the grabbed images in a multi-camera application.

        \code
        Timestamp last_image_timestamp = zed.getTimestamp(TIME_REFERENCE::IMAGE);
        Timestamp current_timestamp = zed.getTimestamp(TIME_REFERENCE::CURRENT);

        std::cout << "Latest image timestamp: " << last_image_timestamp << "ns from Epoch." << std::endl;
        std::cout << "Current timestamp: " << current_timestamp << "ns from Epoch." << std::endl;
        \endcode
         */
        Timestamp getTimestamp(sl::TIME_REFERENCE reference_time);

        /**
        \brief Returns the number of frames dropped since \ref grab() was called for the first time.

        A dropped frame corresponds to a frame that never made it to the grab method.
        \n This can happen if two frames were extracted from the camera when grab() is called. The older frame will be dropped so as to always use the latest (which minimizes latency).

        \return The number of frames dropped since the first \ref grab() call.
         */
        unsigned int getFrameDroppedCount();

        /**
        \brief Returns the current playback position in the SVO file.

        The position corresponds to the number of frames already read from the SVO file, starting from 0 to n.
        \n Each \ref grab() call increases this value by one (except when using \ref InitParameters.svo_real_time_mode).

        \return The current frame position in the SVO file. Returns -1 if the SDK is not reading an SVO.

        \note The method works only if the camera is open in SVO playback mode.
        \see setSVOPosition() for an example.
         */
        int getSVOPosition();


        /**
         * \brief Retrieves the frame index within the SVO file corresponding to the provided timestamp.
         *
         * \param timestamp The target timestamp for which the frame index is to be determined.
         * \return The frame index within the SVO file that aligns with the given timestamp.
         *         Returns -1 if the timestamp falls outside the bounds of the SVO file.
         */

        int getSVOPositionAtTimestamp(const sl::Timestamp &timestamp);

        /**
        \brief Sets the playback cursor to the desired frame number in the SVO file.

        This method allows you to move around within a played-back SVO file. After calling, the next call to \ref grab() will read the provided frame number.

        \param frame_number : The number of the desired frame to be decoded.

        \note The method works only if the camera is open in SVO playback mode.

        \code
        #include <sl/Camera.hpp>

        using namespace sl;

        int main(int argc, char **argv) {

                // Create a ZED camera object
                Camera zed;

                // Set configuration parameters
                InitParameters init_params;
                init_params.input.setFromSVOFile("path/to/my/file.svo");

                // Open the camera
                ERROR_CODE err = zed.open(init_params);
                if (err != ERROR_CODE::SUCCESS) {
                        std::cout << toString(err) << std::endl;
                        exit(-1);
                }

                // Loop between frames 0 and 50
                Mat leftImage;
                while (zed.getSVOPosition() < zed.getSVONumberOfFrames() - 1) {

                        std::cout << "Current frame: " << zed.getSVOPosition() << std::endl;

                        // Loop if we reached frame 50
                        if (zed.getSVOPosition() == 50)
                                zed.setSVOPosition(0);

                        // Grab an image
                        if (zed.grab() == ERROR_CODE::SUCCESS) {
                                zed.retrieveImage(leftImage, VIEW::LEFT); // Get the rectified left image

                                // Use the image in your application
                        }
                }

                // Close the Camera
                zed.close();
                return 0;
        }
        \endcode
         */
        void setSVOPosition(int frame_number);

        /**
        \brief Returns the number of frames in the SVO file.
        \return The total number of frames in the SVO file. -1 if the SDK is not reading a SVO.

        \note The method works only if the camera is open in SVO playback mode.
        \see setSVOPosition() for an example.
         */
        int getSVONumberOfFrames();

        /**
        \brief Ingest SVOData in a SVO file.
        \param data : Data to ingest in the SVO file.
        \return sl::ERROR_CODE::SUCCESS in case of success, sl::ERROR_CODE::FAILURE otherwise.

        \note The method works only if the camera is recording.
         */
        ERROR_CODE ingestDataIntoSVO(const sl::SVOData& data);

        /**
        \brief Retrieves SVO data from the SVO file at the given channel key and in the given timestamp range.
        \param key : The key of the SVOData that is going to be retrieved.
        \param data : The map to be filled with SVOData objects, with timestamps as keys.
        \param ts_begin : The beginning of the range.
        \param ts_end : The end of the range.
        \return sl::ERROR_CODE::SUCCESS in case of success, sl::ERROR_CODE::FAILURE otherwise.

        \note The method works only if the camera is in SVO mode.
         */
        ERROR_CODE retrieveSVOData(const std::string& key, std::map<sl::Timestamp, sl::SVOData>& data, sl::Timestamp ts_begin = 0, sl::Timestamp ts_end = 0);

        /**
        \brief Get the external channels that can be retrieved from the SVO file.
       
        \return List of available keys.

        \note The method returns an empty std::vector if not in SVO mode.
         */
        std::vector<std::string> getSVODataKeys();

        ///@{
        /// @name Depth Sensing
        // -----------------------------------------------------------------
        //                         Depth functions:
        // -----------------------------------------------------------------

        /**
        \brief Computed measures, like depth, point cloud, or normals, can be retrieved using this method.

        Multiple measures are available after a \ref grab() call. A full list is available \ref MEASURE "here".
        \n
        \n <b>Memory</b>
        \n By default, images are copied from GPU memory to CPU memory (RAM) when this function is called.
        \n If your application can use GPU images, using the \b type parameter can increase performance by avoiding this copy.
        \n If the provided \ref Mat object is already allocated and matches the requested image format, memory won't be re-allocated.
        \n
        \n <b>Measure size</b>
        \n By default, measures are returned in the resolution provided by \ref getCameraInformation().camera_configuration.resolution .
        \n However, custom resolutions can be requested. For example, requesting a smaller measure can help you speed up your application.

        \warning A sl::Mat resolution higher than the camera resolution <b>cannot</b> be requested.


        \param mat  : The \ref Mat to store the measure. The method will create the Mat if necessary at the proper resolution. If already created, it will just update its data (CPU or GPU depending on the MEM type).
        \param measure : Defines the measure you want (see \ref MEASURE). Default: \ref MEASURE "MEASURE::DEPTH".
        \param type : Defines on which memory the image should be allocated. Default: \ref MEM "MEM::CPU".
        \param image_size : If specified, define the resolution of the output sl::Mat. If set to \ref Resolution "Resolution(0,0)", the camera resolution will be taken. Default: (0,0).
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the method succeeded.
        \return \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_PARAMETERS" if the view mode requires a module not enabled (\ref VIEW "VIEW::DEPTH" with \ref DEPTH_MODE "DEPTH_MODE::NONE" for example).
        \return \ref ERROR_CODE "ERROR_CODE::INVALID_RESOLUTION" if the resolution is higher than one provided by \ref Resolution "getCameraInformation().camera_configuration.resolution".
        \return \ref ERROR_CODE "ERROR_CODE::FAILURE" if another error occurred.

        \note As this function retrieves the measures computed by the \ref grab() function, This function should be called after a grab() call that returns \ref ERROR_CODE "ERROR_CODE::SUCCESS".
        
        \note Measures containing "RIGHT" in their names, requires \ref InitParameters.enable_right_side_measure to be enabled.

        \code
        Mat imageMap, depthMap, pointCloud;
        sl::Resolution resolution = zed.getCameraInformation().camera_configuration.resolution;
        int x = resolution.width / 2; // Center coordinates
        int y = resolution.height / 2;

        while (true) {
                if (zed.grab() == ERROR_CODE::SUCCESS) { // Grab an image
                        zed.retrieveImage(imageMap, VIEW::LEFT); // Get the image if necessary
                        zed.retrieveMeasure(depthMap, MEASURE::DEPTH, MEM::CPU); // Get the depth map
                        // Read a depth value
                        float centerDepth = 0;
                        depthMap.getValue<float>(x, y, &centerDepth, MEM::CPU); // each depth map pixel is a float value
                        if (std::isnormal(centerDepth)) { // + Inf is "too far", -Inf is "too close", Nan is "unknown/occlusion"
                                std::cout << "Depth value at center: " << centerDepth << " " << init_params.coordinate_units << std::endl;
                        }

                        zed.retrieveMeasure(pointCloud, MEASURE::XYZBGRA, MEM::CPU);// Get the point cloud
                        // Read a point cloud value
                        sl::float4 pcValue;
                        pointCloud.getValue<sl::float4>(x, y, &pcValue); // each point cloud pixel contains 4 floats, so we are using a sl::float4
                        if (std::isnormal(pcValue.z)) {
                                std::cout << "Point cloud coordinates at center: X=" << pcValue.x << ", Y=" << pcValue.y << ", Z=" << pcValue.z << std::endl;
                                unsigned char color[sizeof(float)];
                                memcpy(color, &pcValue[3], sizeof(float));
                                std::cout << "Point cloud color at center: B=" << (int)color[0] << ", G=" << (int)color[1] << ", R=" << (int)color[2] << std::endl;
                        }
                }
        }
        \endcode
         */

        ERROR_CODE retrieveMeasure(Mat& mat, MEASURE measure = MEASURE::DEPTH, MEM type = MEM::CPU, Resolution image_size = Resolution(0, 0));


        /**
        \brief Defines a region of interest to focus on for all the SDK, discarding other parts.
        \param roi_mask: The \ref Mat defining the requested region of interest, pixels lower than 127 will be discarded from all modules: depth, positional tracking, etc.
        If empty, set all pixels as valid. The mask can be either at lower or higher resolution than the current images.
        \param module: Apply the ROI to a list of SDK module, all by default
        \return An \ref ERROR_CODE if something went wrong.
        \note The method support \ref MAT_TYPE "U8_C1/U8_C3/U8_C4" images type.
         */
        ERROR_CODE setRegionOfInterest(sl::Mat &roi_mask, std::unordered_set<MODULE> module = {MODULE::ALL});

        /**
        \brief Get the previously set or computed region of interest
        \param roi_mask: The \ref Mat returned
        \param image_size: The optional size of the returned mask
        \param module: specify which module to get the ROI
        \return An \ref ERROR_CODE if something went wrong.
         */
        ERROR_CODE getRegionOfInterest(sl::Mat &roi_mask, sl::Resolution image_size = Resolution(0, 0), MODULE module = MODULE::ALL);

        /**
        \brief Start the auto detection of a region of interest to focus on for all the SDK, discarding other parts.
        This detection is based on the general motion of the camera combined with the motion in the scene. 
        The camera must move for this process, an internal motion detector is used, based on the Positional Tracking module. 
        It requires a few hundreds frames of motion to compute the mask.
         
        \param roi_param: The \ref RegionOfInterestParameters defining parameters for the detection
          
        \note This module is expecting a static portion, typically a fairly close vehicle hood at the bottom of the image.
         This module may not work correctly or detect incorrect background area, especially with slow motion, if there's no static element.
         This module work asynchronously, the status can be obtained using \ref getRegionOfInterestAutoDetectionStatus(), the result is either auto applied, 
         or can be retrieve using \ref getRegionOfInterest function.
                  
        \return An \ref ERROR_CODE if something went wrong.
         */
        ERROR_CODE startRegionOfInterestAutoDetection(sl::RegionOfInterestParameters roi_param = sl::RegionOfInterestParameters());

        /**
        \brief Return the status of the automatic Region of Interest Detection
         The automatic Region of Interest Detection is enabled by using \ref startRegionOfInterestAutoDetection
        \return \ref REGION_OF_INTEREST_AUTO_DETECTION_STATE the status
         */
        REGION_OF_INTEREST_AUTO_DETECTION_STATE getRegionOfInterestAutoDetectionStatus();


        /**
        \brief Gets the current range of perceived depth.
        \param min[out] : Minimum depth detected (in selected sl::UNIT).
        \param max[out] : Maximum depth detected (in selected sl::UNIT).
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if values can be extracted, \ref ERROR_CODE "ERROR_CODE::FAILURE" otherwise.
         */
        ERROR_CODE getCurrentMinMaxDepth(float &min, float &max);

        ///@}

        ///@{
        /// @name Positional Tracking
        // -----------------------------------------------------------------
        //                        Positional Tracking functions:
        // -----------------------------------------------------------------

        /**
        \brief Initializes and starts the positional tracking processes.

        This method allows you to enable the position estimation of the SDK. It only has to be called once in the camera's lifetime.
        \n When enabled, the \ref getPosition "position" will be update at each \ref grab() call.
        \n Tracking-specific parameter can be set by providing \ref PositionalTrackingParameters to this method.

        \param tracking_parameters : A structure containing all the specific parameters for the positional tracking. Default: a preset of \ref PositionalTrackingParameters.
        \return \ref ERROR_CODE "ERROR_CODE::FAILURE" if the \ref PositionalTrackingParameters.area_file_path file wasn't found, \ref ERROR_CODE "ERROR_CODE::SUCCESS" otherwise.
        \warning The positional tracking feature benefits from a high framerate. We found HD720@60fps to be the best compromise between image quality and framerate.

        \code
        #include <sl/Camera.hpp>

        using namespace sl;

        int main(int argc, char **argv) {

                // --- Initialize a Camera object and open the ZED
                // Create a ZED camera object
                Camera zed;

                // Set configuration parameters
                InitParameters init_params;
                init_params.camera_resolution = RESOLUTION::HD720; // Use HD720 video mode
                init_params.camera_fps = 60; // Set fps at 60

                // Open the camera
                ERROR_CODE err = zed.open(init_params);
                if (err != ERROR_CODE::SUCCESS) {
                        std::cout << toString(err) << std::endl;
                        exit(-1);
                }

                // Set tracking parameters
                PositionalTrackingParameters track_params;
                track_params.enable_area_memory = true;

                // Enable positional tracking
                err = zed.enablePositionalTracking(track_params);
                if (err != ERROR_CODE::SUCCESS) {
                        std::cout << "Tracking error: " << toString(err) << std::endl;
                        exit(-1);
                }

                // --- Main loop
                while (true) {
                        if (zed.grab() == ERROR_CODE::SUCCESS) { // Grab an image and computes the tracking
                                Pose cameraPose;
                                zed.getPosition(cameraPose, REFERENCE_FRAME::WORLD);
                                std::cout << "Camera position: X=" << cameraPose.getTranslation().x << " Y=" << cameraPose.getTranslation().y << " Z=" << cameraPose.getTranslation().z << std::endl;
                        }
                }

                // --- Close the Camera
                zed.close();
                return 0;
        }
        \endcode
         */
        ERROR_CODE enablePositionalTracking(PositionalTrackingParameters tracking_parameters = PositionalTrackingParameters());

        /**
        \brief Retrieves the estimated position and orientation of the camera in the specified \ref REFERENCE_FRAME "reference frame".

        - Using \ref REFERENCE_FRAME "REFERENCE_FRAME::WORLD", the returned pose relates to the initial position of the camera (\ref PositionalTrackingParameters.initial_world_transform ).
        - Using \ref REFERENCE_FRAME "REFERENCE_FRAME::CAMERA", the returned pose relates to the previous position of the camera.
        
        If the tracking has been initialized with \ref PositionalTrackingParameters.enable_area_memory to true (default), this method can return \ref POSITIONAL_TRACKING_STATE "POSITIONAL_TRACKING_STATE::SEARCHING".
        \n This means that the tracking lost its link to the initial referential and is currently trying to relocate the camera. However, it will keep on providing position estimations.

        \param camera_pose[out] : The pose containing the position of the camera and other information (timestamp, confidence).
        \param reference_frame[in] : Defines the reference from which you want the pose to be expressed. Default: \ref REFERENCE_FRAME "REFERENCE_FRAME::WORLD".
        \return The current \ref POSITIONAL_TRACKING_STATE "state" of the tracking process.
        
        \note Extract Rotation Matrix: Pose.getRotationMatrix()
        \note Extract Translation Vector: Pose.getTranslation()
        \note Extract Orientation / Quaternion: Pose.getOrientation()

        \warning This method requires the tracking to be enabled. \ref enablePositionalTracking() .

        \note The position is provided in the \ref InitParameters.coordinate_system . See \ref COORDINATE_SYSTEM for its physical origin.

        \code
        // --- Main loop
        while (true) {
                if (zed.grab() == ERROR_CODE::SUCCESS) { // Grab an image and computes the tracking
                        Pose cameraPose;
                        zed.getPosition(cameraPose, REFERENCE_FRAME::WORLD);
                        std::cout << "Camera position: X=" << cameraPose.getTranslation().x << " Y=" << cameraPose.getTranslation().y << " Z=" << cameraPose.getTranslation().z << std::endl;
                        std::cout << "Camera Euler rotation: X=" << cameraPose.getEulerAngles().x << " Y=" << cameraPose.getEulerAngles().y << " Z=" << cameraPose.getEulerAngles().z << std::endl;
                        std::cout << "Camera Rodrigues rotation: X=" << cameraPose.getRotationVector().x << " Y=" << cameraPose.getRotationVector().y << " Z=" << cameraPose.getRotationVector().z << std::endl;
                        std::cout << "Camera quaternion orientation: X=" << cameraPose.getOrientation().x << " Y=" << cameraPose.getOrientation().y << " Z=" << cameraPose.getOrientation().z << " W=" << cameraPose.getOrientation().w << std::endl;
                        std::cout << std::endl;
                }
        }
        \endcode
         */
        POSITIONAL_TRACKING_STATE getPosition(Pose& camera_pose, REFERENCE_FRAME reference_frame = REFERENCE_FRAME::WORLD);

        /**
         * @brief Return the current status of positional tracking module.
         * 
         * @return sl::PositionalTrackingStatus current status of positional tracking module. 
         */
        sl::PositionalTrackingStatus getPositionalTrackingStatus();


        /**
        \brief Saves the current area learning file. The file will contain spatial memory data generated by the tracking.

        If the tracking has been initialized with \ref PositionalTrackingParameters.enable_area_memory to true (default), the method allows you to export the spatial memory.
        \n Reloading the exported file in a future session with \ref PositionalTrackingParameters.area_file_path initializes the tracking within the same referential.
        \n This method is asynchronous, and only triggers the file generation. You can use \ref getAreaExportState() to get the export state.
        The positional tracking keeps running while exporting.

        \param area_file_path : Path of an '.area' file to save the spatial memory database in.
        \return \ref ERROR_CODE "ERROR_CODE::FAILURE" if the <b>area_file_path</b> file wasn't found, \ref ERROR_CODE "ERROR_CODE::SUCCESS" otherwise.
        \see getAreaExportState()

        \note This method is asynchronous because the generated data can be heavy, be sure to loop over the  \ref getAreaExportState() method with a waiting time.
        \warning If the camera wasn't moved during the tracking session, or not enough, the spatial memory won't be usable and the file won't be exported.
        \warning The \ref getAreaExportState() method will return \ref AREA_EXPORTING_STATE "AREA_EXPORTING_STATE::FILE_EMPTY".
        \warning A few meters (~3m) of translation or a full rotation should be enough to get usable spatial memory.
        \warning However, as it should be used for relocation purposes, visiting a significant portion of the environment is recommended before exporting.

        \code
        // --- Main loop
        while (true) {
                if (zed.grab() == SUCCESS) { // Grab an image and computes the tracking
                        Pose cameraPose;
                        zed.getPosition(cameraPose, REFERENCE_FRAME::WORLD);
                }
        }

        // Export the spatial memory for future sessions
        zed.saveAreaMap("MyMap.area");
        auto export_state = sl::AREA_EXPORTING_STATE::RUNNING;
        while (export_state == sl::AREA_EXPORTING_STATE::RUNNING) {
                export_state = zed.getAreaExportState();
                sl::sleep_ms(5);
        }
        std::cout << "export state: " << export_state << std::endl;

        // --- Close the Camera
        zed.close(); // The close method will wait for the end of the file creation using getAreaExportState().
        return 0;
        \endcode
         */
        ERROR_CODE saveAreaMap(String area_file_path);

        /**
        \brief Returns the state of the spatial memory export process.

        As \ref saveAreaMap() only starts the exportation, this method allows you to know when the exportation finished or if it failed.

        \return The current \ref AREA_EXPORTING_STATE "state" of the spatial memory export process.
         */
        AREA_EXPORTING_STATE getAreaExportState();

        /**
        \brief Resets the tracking, and re-initializes the position with the given transformation matrix.
        \param path : Position of the camera in the world frame when the method is called.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the tracking has been reset, \ref ERROR_CODE "ERROR_CODE::FAILURE" otherwise.

        \note Please note that this method will also flush the accumulated or loaded spatial memory.
         */
        ERROR_CODE resetPositionalTracking(const Transform& path);

        /**
        \brief Disables the positional tracking.

        The positional tracking is immediately stopped. If a file path is given, \ref saveAreaMap() will be called asynchronously. See \ref getAreaExportState() to get the exportation state.
        \n If the tracking has been enabled, this function will automatically be called by \ref close() .

        \param area_file_path : If set, saves the spatial memory into an '.area' file. Default: (empty)
        \n <b>area_file_path</b> is the name and path of the database, e.g. <i>path/to/file/myArea1.area"</i>.
        \note The '.area' database depends on the depth mode and confidence threshold chosen during the recording. The same mode must be used to reload the database.
         */
        void disablePositionalTracking(String area_file_path = "");

        /**
        \brief Tells if the tracking module is enabled
         */
        bool isPositionalTrackingEnabled();


        /**
        \brief Returns the PositionalTrackingParameters used.
        
        It corresponds to the structure given as argument to the \ref enablePositionalTracking() method.

        \return \ref PositionalTrackingParameters containing the parameters used for positional tracking initialization.
         */
        PositionalTrackingParameters getPositionalTrackingParameters();

        // -----------------------------------------------------------------
        //                        Sensors functions, for ZED2 and ZED-M only (using IMU)
        // -----------------------------------------------------------------


        /**
        \brief Retrieves the SensorsData (IMU, magnetometer, barometer) at a specific time reference.

        - Calling \ref getSensorsData with \ref TIME_REFERENCE "TIME_REFERENCE::CURRENT" gives you the latest sensors data received. Getting all the data requires to call this method at high frame rate in a thread.
        - Calling \ref getSensorsData with \ref TIME_REFERENCE "TIME_REFERENCE::IMAGE" gives you the sensors data at the time of the latest image \ref grab() "grabbed".
        \n
        \n \ref SensorsData object contains the previous \ref SensorsData::IMUData structure that was used in ZED SDK v2.X:
        \n
        \n For IMU data, the values are provided in 2 ways:
        <ul>
                <li><b>Time-fused</b> pose estimation that can be accessed using:
                        <ul><li>\ref SensorsData::IMUData.pose "data.imu.pose"</li></ul>
                </li>
                <li><b>Raw values</b> from the IMU sensor:
                        <ul>
                                <li>\ref SensorsData::IMUData.angular_velocity "data.imu.angular_velocity", corresponding to the gyroscope</li>
                                <li>\ref SensorsData::IMUData.linear_acceleration "data.imu.linear_acceleration", corresponding to the accelerometer</li>
                        </ul> both the gyroscope and accelerometer are synchronized.
                </li>
        </ul>
        
        The delta time between previous and current values can be calculated using \ref data.imu.timestamp

        \note The IMU quaternion (fused data) is given in the specified \ref COORDINATE_SYSTEM of InitParameters.
        
        \param data[out] : The SensorsData variable to store the data.
        \param reference_frame[in]: Defines the reference from which you want the data to be expressed. Default: \ref REFERENCE_FRAME "REFERENCE_FRAME::WORLD".
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if sensors data have been extracted.
        \return \ref ERROR_CODE "ERROR_CODE::SENSORS_NOT_AVAILABLE" if the camera model is a \ref MODEL "MODEL::ZED".
        \return \ref ERROR_CODE "ERROR_CODE::MOTION_SENSORS_REQUIRED" if the camera model is correct but the sensors module is not opened.
        \return \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_PARAMETERS" if the <b>reference_time</b> is not valid. See Warning.
        
        \warning In SVO or STREAM mode, the \ref TIME_REFERENCE "TIME_REFERENCE::CURRENT" is currently not available (yielding \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_PARAMETERS".
        \warning Only the quaternion data and barometer data (if available) at TIME_REFERENCE::IMAGE are available. Other values will be set to 0.

        \code
        if (zed.getSensorsData(sensors_data, TIME_REFERENCE::CURRENT) == ERROR_CODE::SUCCESS) {
                std::cout << " - IMU:\n";
                std::cout << " \t Orientation: {" << sensors_data.imu.pose.getOrientation() << "}\n";
                std::cout << " \t Acceleration: {" << sensors_data.imu.linear_acceleration << "} [m/sec^2]\n";
                std::cout << " \t Angular Velocity: {" << sensors_data.imu.angular_velocity << "} [deg/sec]\n";
                std::cout << " - Magnetometer\n \t Magnetic Field: {" << sensors_data.magnetometer.magnetic_field_calibrated << "} [uT]\n";
                std::cout << " - Barometer\n \t Atmospheric pressure:" << sensors_data.barometer.pressure << " [hPa]\n";

                // retrieves camera sensors temperature
                std::cout << " - Temperature\n";
                float temperature;
                for (int s = 0; s < static_cast<int>(SensorsData::TemperatureData::SENSOR_LOCATION::LAST); s++) {
                        auto sensor_loc = static_cast<SensorsData::TemperatureData::SENSOR_LOCATION>(s);
                        // depending on your Camera model or its firmware, different sensors can give thermal information
                        if (sensors_data.temperature.get(sensor_loc, temperature) == ERROR_CODE::SUCCESS)
                        std::cout << " \t " << sensor_loc << ": " << temperature << "C\n";
                }
        }
        \endcode
         */
        ERROR_CODE getSensorsData(SensorsData& data, TIME_REFERENCE reference_time);

        /**
        \brief Set an optional IMU orientation hint that will be used to assist the tracking during the next \ref grab().

        This method can be used to assist the positional tracking rotation.

        \note This method is only effective if the camera has a model other than a \ref MODEL "MODEL::ZED", which does not contains internal sensors.
        \warning It needs to be called before the \ref grab() method.
        \param sl::Transform to be ingested into IMU fusion. Note that only the rotation is used.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the transform has been passed, \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_CALL" otherwise (e.g. when used with a ZED camera which doesn't have IMU data).
         */
        ERROR_CODE setIMUPrior(const sl::Transform& transform);



        //@}

        ///@{
        /// @name Spatial Mapping
        // -----------------------------------------------------------------
        //                         Spatial Mapping functions:
        // -----------------------------------------------------------------

        /**
        \brief Initializes and starts the spatial mapping processes.

        The spatial mapping will create a geometric representation of the scene based on both tracking data and 3D point clouds.
        \n The resulting output can be a \ref Mesh or a \ref FusedPointCloud. It can be be obtained by calling \ref extractWholeSpatialMap() or \ref retrieveSpatialMapAsync().
        Note that \ref retrieveSpatialMapAsync() should be called after \ref requestSpatialMapAsync().

        \param spatial_mapping_parameters : A structure containing all the specific parameters for the spatial mapping.
        \n Default: a balanced parameter preset between geometric fidelity and output file size. For more information, see the \ref SpatialMappingParameters documentation.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if everything went fine, \ref ERROR_CODE "ERROR_CODE::FAILURE" otherwise.

        \warning The tracking (\ref enablePositionalTracking() ) and the depth (\ref RuntimeParameters.enable_depth ) needs to be enabled to use the spatial mapping.
        \warning The performance greatly depends on the <b>spatial_mapping_parameters</b>.
        \warning Lower SpatialMappingParameters.range_meter and SpatialMappingParameters.resolution_meter for higher performance.
        If the mapping framerate is too slow in live mode, consider using an SVO file, or choose a lower mesh resolution.

        \note This feature uses host memory (RAM) to store the 3D map. The maximum amount of available memory allowed can be tweaked using the SpatialMappingParameters.
        \n Exceeding the maximum memory allowed immediately stops the mapping.

        \code
        #include <sl/Camera.hpp>

        using namespace sl;

        int main(int argc, char **argv) {

                // Create a ZED camera object
                Camera zed;

                // Set initial parameters
                InitParameters init_params;
                init_params.camera_resolution = RESOLUTION::HD720; // Use HD720 video mode (default fps: 60)
                init_params.coordinate_system = COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP; // Use a right-handed Y-up coordinate system (The OpenGL one)
                init_params.coordinate_units = UNIT::METER; // Set units in meters

                // Open the camera
                ERROR_CODE err = zed.open(init_params);
                if (err != ERROR_CODE::SUCCESS)
                        exit(-1);

                // Positional tracking needs to be enabled before using spatial mapping
                sl::PositionalTrackingParameters tracking_parameters;
                err = zed.enablePositionalTracking(tracking_parameters);
                if (err != ERROR_CODE::SUCCESS)
                        exit(-1);

                // Enable spatial mapping
                sl::SpatialMappingParameters mapping_parameters;
                err = zed.enableSpatialMapping(mapping_parameters);
                if (err != ERROR_CODE::SUCCESS)
                        exit(-1);

                // Grab data during 500 frames
                int i = 0;
                sl::Mesh mesh; // Create a mesh object
                while (i < 500) {
                        // For each new grab, mesh data is updated
                        if (zed.grab() == ERROR_CODE::SUCCESS) {
                                // In the background, the spatial mapping will use newly retrieved images, depth and pose to update the mesh
                                sl::SPATIAL_MAPPING_STATE mapping_state = zed.getSpatialMappingState();

                                // Print spatial mapping state
                                std::cout << "Images captured: " << i << " / 500  ||  Spatial mapping state: " << mapping_state << std::endl;
                                i++;
                        }
                }
                std::cout << std::endl;

                // Extract, filter and save the mesh in a obj file
                std::cout << "Extracting Mesh ..." << std::endl;
                zed.extractWholeSpatialMap(mesh); // Extract the whole mesh
                std::cout << "Filtering Mesh ..." << std::endl;
                mesh.filter(sl::MeshFilterParameters::MESH_FILTER::LOW); // Filter the mesh (remove unnecessary vertices and faces)
                std::cout << "Saving Mesh in mesh.obj ..." << std::endl;
                mesh.save("mesh.obj"); // Save the mesh in an obj file


                // Disable tracking and mapping and close the camera
                zed.disableSpatialMapping();
                zed.disablePositionalTracking();
                zed.close();
                return 0;
        }
        \endcode
         */
        ERROR_CODE enableSpatialMapping(SpatialMappingParameters spatial_mapping_parameters = SpatialMappingParameters());

        /**
        \brief Returns the current spatial mapping state.

        As the spatial mapping runs asynchronously, this method allows you to get reported errors or status info.

        \return The current state of the spatial mapping process.
        \see SPATIAL_MAPPING_STATE
         */
        SPATIAL_MAPPING_STATE getSpatialMappingState();

        // -----------------------------------------------------------------
        // Async functions of spatial map generation ( *Async())
        // -----------------------------------------------------------------
        /**
        \brief Starts the spatial map generation process in a non-blocking thread from the spatial mapping process.

        The spatial map generation can take a long time depending on the mapping resolution and covered area. This function will trigger the generation of a mesh without blocking the program.
        \n You can get info about the current generation using \ref getSpatialMapRequestStatusAsync(), and retrieve the mesh using \ref retrieveSpatialMapAsync() .

        \note Only one mesh can be generated at a time. If the previous mesh generation is not over, new calls of the function will be ignored.

        See \ref enableSpatialMapping() for an example.
         */
        void requestSpatialMapAsync();

        /**
        \brief Returns the spatial map generation status.
        
        This status allows to know if the mesh can be retrieved by calling \ref retrieveSpatialMapAsync .
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the mesh is ready and not yet retrieved, otherwise \ref ERROR_CODE "ERROR_CODE::FAILURE".

        See \ref enableSpatialMapping() for an example.
         */
        ERROR_CODE getSpatialMapRequestStatusAsync();

        /**
        \brief Retrieves the current generated spatial map only if \ref SpatialMappingParameters::map_type was set as \ref SpatialMappingParameters::SPATIAL_MAP_TYPE "MESH".

        After calling \ref requestSpatialMapAsync(), this method allows you to retrieve the generated mesh.
        \n The mesh will only be available when \ref getSpatialMapRequestStatusAsync() returns \ref ERROR_CODE "ERROR_CODE::SUCCESS".

        \param mesh[out] : The mesh to be filled with the generated spatial map.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the mesh is retrieved, otherwise \ref ERROR_CODE "ERROR_CODE::FAILURE".

        \note This method only updates the necessary chunks and adds the new ones in order to improve update speed.
        \warning You should not modify the mesh between two calls of this method, otherwise it can lead to a corrupted mesh.
        \warning If the SpatialMappingParameters::map_type has not been setup as \ref SpatialMappingParameters::SPATIAL_MAP_TYPE "MESH", the object will be empty.
        
        See \ref enableSpatialMapping() for an example.
         */
        ERROR_CODE retrieveSpatialMapAsync(Mesh& mesh);

        /**
        \brief Retrieves the current generated spatial map only if \ref SpatialMappingParameters::map_type was set as \ref SpatialMappingParameters::SPATIAL_MAP_TYPE "FUSED_POINT_CLOUD".

        After calling \ref requestSpatialMapAsync(), this method allows you to retrieve the generated fused point cloud.
        \n The fused point cloud will only be available when \ref getSpatialMapRequestStatusAsync() returns \ref ERROR_CODE "ERROR_CODE::SUCCESS".

        \param fpc[out] : The fused point cloud to be filled with the generated spatial map.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the mesh is retrieved, otherwise \ref ERROR_CODE "ERROR_CODE::FAILURE".

        \note This method only updates the necessary chunks and adds the new ones in order to improve update speed.
        \warning You should not modify the fused point cloud between two calls of this method, otherwise it can lead to a corrupted fused point cloud.
        \warning If the SpatialMappingParameters::map_type has not been setup as \ref SpatialMappingParameters::SPATIAL_MAP_TYPE "FUSED_POINT_CLOUD", the object will be empty.

        See \ref enableSpatialMapping() for an example.
         */
        ERROR_CODE retrieveSpatialMapAsync(FusedPointCloud& fpc);

        // -----------------------------------------------------------------
        // Blocking (synchronous) function of spatial map generation
        // -----------------------------------------------------------------
        /**
        \brief Extract the current spatial map from the spatial mapping process only if \ref SpatialMappingParameters::map_type was set as \ref SpatialMappingParameters::SPATIAL_MAP_TYPE "MESH".

        If the object to be filled already contains a previous version of the mesh, only changes will be updated, optimizing performance.

        \param mesh[out] : The mesh to be filled with the generated spatial map.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the mesh is filled and available, otherwise \ref ERROR_CODE "ERROR_CODE::FAILURE".

        \warning This is a blocking method. You should either call it in a thread or at the end of the mapping process.
        \n The extraction can be long, calling this method in the grab loop will block the depth and tracking computation giving bad results.

        \warning If the SpatialMappingParameters::map_type has not been setup as \ref SpatialMappingParameters::SPATIAL_MAP_TYPE "MESH", the object will be empty.
        
        See \ref enableSpatialMapping() for an example.
         */
        ERROR_CODE extractWholeSpatialMap(Mesh& mesh);

        /**
        \brief Extract the current spatial map from the spatial mapping process only if \ref SpatialMappingParameters::map_type was set as \ref SpatialMappingParameters::SPATIAL_MAP_TYPE "FUSED_POINT_CLOUD".

        If the object to be filled already contains a previous version of the fused point cloud, only changes will be updated, optimizing performance.

        \param fpc[out] : The fused point cloud to be filled with the generated spatial map.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the fused point cloud is filled and available, otherwise \ref ERROR_CODE "ERROR_CODE::FAILURE".

        \warning This is a blocking method. You should either call it in a thread or at the end of the mapping process.
        \n The extraction can be long, calling this method in the grab loop will block the depth and tracking computation giving bad results.
        \warning If the SpatialMappingParameters::map_type has not been setup as \ref SpatialMappingParameters::SPATIAL_MAP_TYPE "FUSED_POINT_CLOUD", the object will be empty.
        
        See \ref enableSpatialMapping() for an example.
         */
        ERROR_CODE extractWholeSpatialMap(FusedPointCloud& fpc);

        /**
        \brief Pauses or resumes the spatial mapping processes.

        As spatial mapping runs asynchronously, using this method can pause its computation to free some processing power, and resume it again later.
        \n For example, it can be used to avoid mapping a specific area or to pause the mapping when the camera is static.

        \param status : If true, the integration is paused. If false, the spatial mapping is resumed.
         */
        void pauseSpatialMapping(bool status);

        /**
        \brief Disables the spatial mapping process.

        The spatial mapping is immediately stopped.
        \n If the mapping has been enabled, this method will automatically be called by \ref close().

        \note This method frees the memory allocated for the spatial mapping, consequently, meshes and fused point clouds cannot be retrieved after this call.
         */
        void disableSpatialMapping();

        /**
        \brief Returns the SpatialMappingParameters used.
        
        It corresponds to the structure given as argument to the enableSpatialMapping() method.

        \return \ref SpatialMappingParameters containing the parameters used for spatial mapping initialization.
         */
        SpatialMappingParameters getSpatialMappingParameters();

        ///@}



        /**
        \brief Checks the plane at the given left image coordinates.

        This method gives the 3D plane corresponding to a given pixel in the latest left image \ref grab() "grabbed".
        \n The pixel coordinates are expected to be contained x=[0;width-1] and y=[0;height-1], where width/height are defined by the input resolution.

        \param coord[in] : The image coordinate. The coordinate must be taken from the full-size image.
        \param plane[out] :  The detected plane if the method succeeded.
        \param parameters[in] :  A structure containing all the specific parameters for the plane detection. Default: a preset of PlaneDetectionParameters.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if a plane is found, otherwise \ref ERROR_CODE "ERROR_CODE::PLANE_NOT_FOUND".
        \note The reference frame is defined by the \ref RuntimeParameters.measure3D_reference_frame given to the \ref grab() method.
         */
        ERROR_CODE findPlaneAtHit(sl::uint2 coord, sl::Plane& plane, PlaneDetectionParameters parameters = PlaneDetectionParameters());

        /**
        \brief Detect the floor plane of the scene.

        This method analysis the latest image and depth to estimate the floor plane of the scene.
        \n It expects the floor plane to be visible and bigger than other candidate planes, like a table.

        \param floorPlane[out] : The detected floor plane if the method succeeded.
        \param resetTrackingFloorFrame[out] : The transform to align the tracking with the floor plane.
        \n The initial position will then be at ground height, with the axis align with the gravity.
        \n The positional tracking needs to be reset/enabled with this transform as a parameter (PositionalTrackingParameters.initial_world_transform).
        \param floor_height_prior[in] : Prior set to locate the floor plane depending on the known camera distance to the ground, expressed in the same unit as the ZED.
        \n If the prior is too far from the detected floor plane, the method will return \ref ERROR_CODE "ERROR_CODE::PLANE_NOT_FOUND".
        \param world_orientation_prior[in] : Prior set to locate the floor plane depending on the known camera orientation to the ground.
        \n If the prior is too far from the detected floor plane, the method will return \ref ERROR_CODE "ERROR_CODE::PLANE_NOT_FOUND.
        \param floor_height_prior_tolerance[in] : Prior height tolerance, absolute value.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if the floor plane is found and matches the priors (if defined), otherwise \ref ERROR_CODE "ERROR_CODE::PLANE_NOT_FOUND".
        \note The reference frame is defined by the sl::RuntimeParameters (measure3D_reference_frame) given to the grab() method.
        \note The length unit is defined by sl:InitParameters (coordinate_units).
        \note With the ZED, the assumption is made that the floor plane is the dominant plane in the scene. The ZED Mini uses gravity as prior.
         */
        ERROR_CODE findFloorPlane(sl::Plane& floorPlane, sl::Transform& resetTrackingFloorFrame,
                float floor_height_prior = INVALID_VALUE, sl::Rotation world_orientation_prior = sl::Matrix3f::zeros(),
                float floor_height_prior_tolerance = INVALID_VALUE);

        ///@}


        ///@{
        /// @name Recording
        // -----------------------------------------------------------------
        //                 		Recording functions
        // -----------------------------------------------------------------

        /**
        \brief Creates an SVO file to be filled by enableRecording() and disableRecording().


        \n SVO files are custom video files containing the un-rectified images from the camera along with some meta-data like timestamps or IMU orientation (if applicable).
        \n They can be used to simulate a live ZED and test a sequence with various SDK parameters.
        \n Depending on the application, various compression modes are available. See \ref SVO_COMPRESSION_MODE.

        \param recording_parameters : A structure containing all the specific parameters for the recording such as filename and compression mode. Default: a reset of RecordingParameters .
        \return An \ref ERROR_CODE that defines if the SVO file was successfully created and can be filled with images.

        \warning This method can be called multiple times during a camera lifetime, but if <b>video_filename</b> is already existing, the file will be erased.

        \code
        #include <sl/Camera.hpp>

        using namespace sl;

        int main(int argc, char **argv) {

                // Create a ZED camera object
                Camera zed;

                // Set initial parameters
                InitParameters init_params;
                init_params.camera_resolution = RESOLUTION::HD720; // Use HD720 video mode (default fps: 60)
                init_params.coordinate_units = UNIT::METER; // Set units in meters

                // Open the camera
                ERROR_CODE err = zed.open(init_params);
                if (err != ERROR_CODE::SUCCESS) {
                        std::cout << toString(err) << std::endl;
                        exit(-1);
                }

                // Enable video recording
                err = zed.enableRecording(RecordingParameters("myVideoFile.svo", SVO_COMPRESSION_MODE::H264));
                if (err != ERROR_CODE::SUCCESS) {
                        std::cout << toString(err) << std::endl;
                        exit(-1);
                }

                // Grab data during 500 frames
                int i = 0;
                while (i < 500) {
                        // Grab a new frame
                        if (zed.grab() == ERROR_CODE::SUCCESS) {
                                // Record the grabbed frame in the video file
                                i++;
                        }
                }

                zed.disableRecording();
                std::cout << "Video has been saved ..." << std::endl;

                zed.close();
                return 0;
        }
        \endcode
         */
        ERROR_CODE enableRecording(RecordingParameters recording_parameters);

        /**
        \brief Get the recording information.
        \return The recording state structure. For more details, see \ref RecordingStatus.
         */
        RecordingStatus getRecordingStatus();

        /**
        \brief Pauses or resumes the recording.
        \param status : If true, the recording is paused. If false, the recording is resumed.
         */
        void pauseRecording(bool status);

        /**
        \brief Disables the recording initiated by \ref enableRecording() and closes the generated file.

        \note This method will automatically be called by \ref close() if enableRecording() was called.

        See \ref enableRecording() for an example.

         */
        void disableRecording();

        /**
        \brief Returns the RecordingParameters used.
        
        It corresponds to the structure given as argument to the enableRecording() method.

        \return \ref RecordingParameters containing the parameters used for recording initialization.
         */
        RecordingParameters getRecordingParameters();
        ///@}

        ///@{
        /// @name Streaming
        // -----------------------------------------------------------------
        //                 		Streaming functions
        // -----------------------------------------------------------------
        /**
        \brief Creates a streaming pipeline.
        \param streaming_parameters : A structure containing all the specific parameters for the streaming. Default: a reset of StreamingParameters .
        \return\ref ERROR_CODE "ERROR_CODE::SUCCESS" if streaming was successfully started.
        \return\ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_CALL" if open() was not successfully called before.
        \return\ref ERROR_CODE "ERROR_CODE::FAILURE" if streaming RTSP protocol was not able to start.
        \return\ref ERROR_CODE "ERROR_CODE::NO_GPU_COMPATIBLE" if streaming codec is not supported (in this case, use H264 codec which is supported on all NVIDIA GPU the ZED SDK supports).
        
        \code
        #include <sl/Camera.hpp>

        using namespace sl;

        int main(int argc, char **argv) {

                // Create a ZED camera object
                Camera zed;

                // Open the camera
                ERROR_CODE err = zed.open();
                if (err != ERROR_CODE::SUCCESS) {
                        std::cout << toString(err) << std::endl;
                        exit(-1);
                }

                // Enable video recording
                sl::StreamingParameters stream_params;
                err = zed.enableStreaming(stream_params);
                if (err != ERROR_CODE::SUCCESS) {
                        std::cout << toString(err) << std::endl;
                        exit(-1);
                }

                // Grab data during 500 frames
                int i = 0;
                while (i < 500) {
                        // Grab a new frame
                        if (zed.grab() == ERROR_CODE::SUCCESS) 
                                i++;                        
                }

                zed.disableStreaming();
                zed.close();
                return 0;
        }
        \endcode
         */
        ERROR_CODE enableStreaming(StreamingParameters streaming_parameters = StreamingParameters());

        /**
        \brief Disables the streaming initiated by \ref enableStreaming().
        \note This method will automatically be called by \ref close() if enableStreaming() was called.
        
        See \ref enableStreaming() for an example.
         */
        void disableStreaming();

        /**
        \brief Tells if the streaming is running.
        \return true if the stream is running, false otherwise.
         */
        bool isStreamingEnabled();

        /**
        \brief Returns the StreamingParameters used.
        
        It corresponds to the structure given as argument to the enableStreaming() method.

        \return \ref StreamingParameters containing the parameters used for streaming initialization.
         */
        StreamingParameters getStreamingParameters();

        ///@}

        ///@{
        /// @name Object Detection
        // -----------------------------------------------------------------
        //                         Object Detection functions:
        // -----------------------------------------------------------------

        /**
        \brief Initializes and starts object detection module.
        
        The object detection module currently supports multiple class of objects with the \ref OBJECT_DETECTION_MODEL "OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX"
        or \ref OBJECT_DETECTION_MODEL "OBJECT_DETECTION_MODEL::MULTI_CLASS_BOX_ACCURATE".
        \n The full list of detectable objects is available through \ref OBJECT_CLASS and \ref OBJECT_SUBCLASS.

        \n Detected objects can be retrieved using the \ref retrieveObjects() method.

        \note - <b>This Depth Learning detection module is not available \ref MODEL "MODEL::ZED" cameras</b>.
        \note - This feature uses AI to locate objects and requires a powerful GPU. A GPU with at least 3GB of memory is recommended.

        \param object_detection_parameters : A structure containing all the specific parameters for the object detection. Default: a preset of ObjectDetectionParameters.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if everything went fine.
        \return \ref ERROR_CODE "ERROR_CODE::CORRUPTED_SDK_INSTALLATION" if the AI model is missing or corrupted. In this case, the SDK needs to be reinstalled.
        \return \ref ERROR_CODE "ERROR_CODE::MODULE_NOT_COMPATIBLE_WITH_CAMERA" if the camera used does not have a IMU (\ref MODEL "MODEL::ZED").
        \return \ref ERROR_CODE "ERROR_CODE::MOTION_SENSORS_REQUIRED" if the camera model is correct (not \ref MODEL "MODEL.ZED") but the IMU is missing. It probably happens because InitParameters::sensors_required was set to false and that IMU has not been found.
        \return \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_CALL" if one of the <b>object_detection_parameters</b> parameter is not compatible with other modules parameters (for example, <b>depth_mode</b> has been set to \ref DEPTH_MODE "DEPTH_MODE::NONE").
        \return \ref ERROR_CODE "ERROR_CODE::FAILURE" otherwise.

        \note The IMU gives the gravity vector that helps in the 3D box localization. Therefore the object detection module is not available for the \ref MODEL "MODEL::ZED" camera model.

        \code
        #include <sl/Camera.hpp>

        using namespace sl;

        int main(int argc, char **argv) {
            // Create a ZED camera object
            Camera zed;

            // Open the camera
            ERROR_CODE err = zed.open();
            if (err != ERROR_CODE::SUCCESS) {
                std::cout << "Opening camera error: " << toString(err) << std::endl;
                exit(-1);
            }

            // Enable position tracking (mandatory for object detection)
            PositionalTrackingParameters tracking_params;
            err = zed.enablePositionalTracking(tracking_params);
            if (err != ERROR_CODE::SUCCESS) {
                std::cout << "Enabling Positional Tracking error: " << toString(err) << std::endl;
                exit(-1);
            }

            // Set the object detection parameters
            ObjectDetectionParameters object_detection_params;

            // Enable the object detection
            err = zed.enableObjectDetection(object_detection_params);
            if (err != ERROR_CODE::SUCCESS) {
                std::cout << "Enabling Object Detection error: " << toString(err) << std::endl;
                exit(-1);
            }

            // Grab an image and detect objects on it
            Objects objects;
            while (true) {
                if (zed.grab() == ERROR_CODE::SUCCESS) {
                    zed.retrieveObjects(objects);
                    std::cout << objects.object_list.size() << " objects detected " << std::endl;
                    // Use the objects in your application
                }
            }

            // Close the Camera
            zed.disableObjectDetection();
            zed.close();
            return 0;
        }
        \endcode
         */
        ERROR_CODE enableObjectDetection(ObjectDetectionParameters object_detection_parameters = ObjectDetectionParameters());


        /**
        \brief Disables the Object Detection process.

        The object detection module immediately stops and frees its memory allocations.
        
        \param instance_id : Id of the object detection instance. Used when multiple instances of the object detection module are enabled at the same time.
        \param force_disable_all_instances : Should disable all instances of the object detection module or just <b>instance_id</b>.
        
        \note If the object detection has been enabled, this method will automatically be called by \ref close().
         */
        void disableObjectDetection(unsigned int instance_id = 0, bool force_disable_all_instances = false);

        /**
        \brief Feed the 3D Object tracking method with your own 2D bounding boxes from your own detection algorithm.
        
        \param objects_in : Vector of CustomBoxObjectData to feed the object detection.
        \param instance_id : Id of the object detection instance. Used when multiple instances of the object detection module are enabled at the same time.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if everything went fine.

        \note The detection should be done on the current grabbed left image as the internal process will use all currently available data to extract 3D informations and perform object tracking.
         */
        ERROR_CODE ingestCustomBoxObjects(std::vector<CustomBoxObjectData> &objects_in, unsigned int instance_id = 0);


        /**
        \brief Retrieve objects detected by the object detection module.

        This method returns the result of the object detection, whether the module is running synchronously or asynchronously.

        - <b>Asynchronous:</b> this method immediately returns the last objects detected. If the current detection isn't done, the objects from the last detection will be returned, and \ref Objects::is_new will be set to false.
        - <b>Synchronous:</b> this method executes detection and waits for it to finish before returning the detected objects.

        It is recommended to keep the same \ref Objects object as the input of all calls to this method. This will enable the identification and tracking of every object detected.

        \param objects : The detected objects will be saved into this object. If the object already contains data from a previous detection, it will be updated, keeping a unique ID for the same person.
        \param parameters : Object detection runtime settings, can be changed at each detection. In async mode, the parameters update is applied on the next iteration.
        \param instance_id : Id of the object detection instance. Used when multiple instances of the object detection module are enabled at the same time.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if everything went fine, \ref ERROR_CODE "ERROR_CODE::FAILURE" otherwise.

        \code
        Objects objects; // Unique Objects to be updated after each grab
        // --- Main loop
        while (true) {
            if (zed.grab() == ERROR_CODE::SUCCESS) { // Grab an image from the camera
                zed.retrieveObjects(objects);
                for (auto object : objects.object_list) {
                    std::cout << object.label << std::endl;
                }
            }
        }
        \endcode
         *
         */
        ERROR_CODE retrieveObjects(Objects &objects, ObjectDetectionRuntimeParameters parameters = ObjectDetectionRuntimeParameters(), unsigned int instance_id = 0);

        /**
        \brief Get a batch of detected objects.

        \warning This method need to be called after retrieveObjects, otherwise trajectories will be empty.
        It is the \ref retrieveObjects method that ingest the current/live objects into the batching queue.

        \param trajectories as a std::vector of \ref sl::ObjectsBatch, that will be filled by the batching queue process.
        \param instance_id : Id of the object detection instance. Used when multiple instances of the object detection module are enabled at the same time.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if everything went fine.
        \return \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_CALL" if batching module is not available or if object tracking was not enabled.

        \note Most of the time, the vector will be empty and will be filled every \ref BatchParameters::latency.

        \code
        Objects objects; // Unique Objects to be updated after each grab
        // --- Main loop
        while (true) {
            if (zed.grab() == ERROR_CODE::SUCCESS) { // Grab an image from the camera
                   //Call retrieveObjects so that objects are ingested in the batching system
                   zed.retrieveObjects(objects);

                   // Get batch of objects
                   std::vector<sl::ObjectsBatch> traj_;
                   zed.getObjectsBatch(traj_);
                   std::cout<<" Size of batch: "<<traj_.size()<<std::endl;

                   // See zed-examples/object detection/birds eye viewer for a complete example.
            }
        }
        \endcode
         */
        ERROR_CODE getObjectsBatch(std::vector<sl::ObjectsBatch>& trajectories, unsigned int instance_id = 0);

        /**
        \brief Tells if the object detection module is enabled.
         */
        bool isObjectDetectionEnabled(unsigned int instance_id = 0);

        /**
        \brief Returns the ObjectDetectionParameters used.

        It corresponds to the structure given as argument to the \ref enableObjectDetection() method.

        \return \ref ObjectDetectionParameters containing the parameters used for object detection initialization.
         */
        ObjectDetectionParameters getObjectDetectionParameters(unsigned int instance_id = 0);

        ///@}


        ///@{
        /// @name Body Tracking
        // -----------------------------------------------------------------
        //                         Body Tracking functions:
        // -----------------------------------------------------------------

        /**
        \brief Initializes and starts body tracking module.

        The body tracking module currently supports multiple classes of human skeleton detection with the \ref BODY_TRACKING_MODEL "BODY_TRACKING_MODEL::HUMAN_BODY_FAST",
        \ref BODY_TRACKING_MODEL "BODY_TRACKING_MODEL::HUMAN_BODY_MEDIUM" and \ref BODY_TRACKING_MODEL "BODY_TRACKING_MODEL::HUMAN_BODY_ACCURATE".
        \n This model only detects humans but provides a full skeleton map for each person.

        \n Detected objects can be retrieved using the \ref retrieveBodies() method.

        \note - <b>This Deep Learning detection module is not available for \ref MODEL "MODEL::ZED" cameras (ZED first generation).</b>.
        \note - This feature uses AI to locate objects and requires a powerful GPU. A GPU with at least 3GB of memory is recommended.

        \param body_tracking_parameters : A structure containing all the specific parameters for the object detection. Default: default BodyTrackingParameters.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if everything went fine.
        \return \ref ERROR_CODE "ERROR_CODE::CORRUPTED_SDK_INSTALLATION" if the AI model is missing or corrupted. In this case, the SDK needs to be reinstalled.
        \return \ref ERROR_CODE "ERROR_CODE::MODULE_NOT_COMPATIBLE_WITH_CAMERA" if the camera used does not have a IMU (\ref MODEL "MODEL::ZED").
        \return \ref ERROR_CODE "ERROR_CODE::MOTION_SENSORS_REQUIRED" if the camera model is correct (not \ref MODEL "MODEL::ZED") but the IMU is missing. It probably happens because InitParameters::sensors_required was set to false and that IMU has not been found.
        \return \ref ERROR_CODE "ERROR_CODE::INVALID_FUNCTION_CALL" if one of the <b>body_tracking_parameters</b> parameter is not compatible with other modules parameters (for example, <b>depth_mode</b> has been set to \ref DEPTH_MODE "DEPTH_MODE::NONE").
        \return \ref ERROR_CODE "ERROR_CODE::FAILURE" otherwise.

        \code
        #include <sl/Camera.hpp>

        using namespace sl;

        int main(int argc, char **argv) {
            // Create a ZED camera object
            Camera zed;

            // Open the camera
            ERROR_CODE err = zed.open();
            if (err != ERROR_CODE::SUCCESS) {
                std::cout << "Opening camera error: " << toString(err) << std::endl;
                exit(-1);
            }

            // Enable position tracking (mandatory for body tracking)
            PositionalTrackingParameters tracking_params;
            err = zed.enablePositionalTracking(tracking_params);
            if (err != ERROR_CODE::SUCCESS) {
                std::cout << "Enabling Positional Tracking error: " << toString(err) << std::endl;
                exit(-1);
            }

            // Set the body tracking parameters
            BodyTrackingParameters body_tracking_params;

            // Enable the body tracking
            err = zed.enableBodyTracking(body_tracking_params);
            if (err != ERROR_CODE::SUCCESS) {
                std::cout << "Enabling Body Tracking error: " << toString(err) << std::endl;
                exit(-1);
            }

            // Grab an image and detect bodies on it
            Bodies bodies;
            while (true) {
                if (zed.grab() == ERROR_CODE::SUCCESS) {
                    zed.retrieveBodies(bodies);
                    std::cout << bodies.body_list.size() << " bodies detected " << std::endl;
                    // Use the bodies in your application
                }
            }

            // Close the Camera
            zed.disableBodyTracking();
            zed.close();
            return 0;
        }
        \endcode
         */
        ERROR_CODE enableBodyTracking(BodyTrackingParameters body_tracking_parameters = BodyTrackingParameters());

        /**
        \brief Disables the body tracking process.

        The body tracking module immediately stops and frees its memory allocations.
        
        \param instance_id : Id of the body tracking instance. Used when multiple instances of the body tracking module are enabled at the same time.
        \param force_disable_all_instances : Should disable all instances of the tracking module module or just <b>instance_id</b>.

        \note If the body tracking has been enabled, this method will automatically be called by \ref close().
         */
        void disableBodyTracking(unsigned int instance_id = 0, bool force_disable_all_instances = false);


        /**
        \brief Retrieves body tracking data from the body tracking module.

        This method returns the result of the body tracking, whether the module is running synchronously or asynchronously.

        - <b>Asynchronous:</b> this method immediately returns the last bodies tracked. If the current tracking isn't done, the bodies from the last tracking will be returned, and \ref Bodies::is_new will be set to false.
        - <b>Synchronous:</b> this method executes detection and waits for it to finish before returning the bodies tracked.

        It is recommended to keep the same \ref Bodies object as the input of all calls to this method. This will enable the identification and the tracking of every detected body.

        \param bodies : The tracked bodies will be saved into this object. If the object already contains data from a previous detection, it will be updated, keeping a unique ID for the same person.
        \param parameters : Body tracking runtime settings, can be changed at each detection. In async mode, the parameters update is applied on the next iteration.
        \param instance_id : Id of the body tracking instance. Used when multiple instances of the body tracking module are enabled at the same time.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if everything went fine, \ref ERROR_CODE "ERROR_CODE::FAILURE" otherwise.

        \code
        Bodies bodies; // Unique Bodies to be updated after each grab
        // --- Main loop
        while (true) {
            if (zed.grab() == ERROR_CODE::SUCCESS) { // Grab an image from the camera
                zed.retrieveBodies(bodies);
                for (auto body : bodies.body_list) {
                    std::cout << body.label << std::endl;
                }
            }
        }
        \endcode
         *
         */
        ERROR_CODE retrieveBodies(Bodies &bodies, BodyTrackingRuntimeParameters parameters = BodyTrackingRuntimeParameters(), unsigned int instance_id = 0);

        /**
        \brief Tells if the body tracking module is enabled.
         */
        bool isBodyTrackingEnabled(unsigned int instance_id = 0);

        /**
        \brief Returns the BodyTrackingParameters used.

        It corresponds to the structure given as argument to the \ref enableBodyTracking() method.

        \return \ref BodyTrackingParameters containing the parameters used for body tracking module initialization.
         */
        BodyTrackingParameters getBodyTrackingParameters(unsigned int instance_id = 0);

        ///@}


        ///@{
        /// @name Fusion
        // -----------------------------------------------------------------
        //                         Fusion functions:
        // -----------------------------------------------------------------

        /**
        \brief Set this camera as a data provider for the Fusion module. 
        
        Metadata is exchanged with the Fusion.
        \note If you use it, you should include <i>sl/Fusion.hpp</i> to avoid undefined reference.
        \param configuration : A structure containing all the initial parameters. Default: a preset of CommunicationParameters.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if everything went fine, \ref ERROR_CODE "ERROR_CODE::FAILURE" otherwise.
         */
        ERROR_CODE startPublishing(CommunicationParameters configuration = CommunicationParameters());

        /**
        \ingroup Fusion_group
        \brief Set this camera as normal camera (without data providing).
        \n Stop to send camera data to fusion.
        \return \ref SUCCESS if everything went fine, \ref ERROR_CODE::FAILURE otherwise
         */
        ERROR_CODE stopPublishing();

        /**
        \ingroup Fusion_group
        \brief Returns the CommunicationParameters used.
        \n It corresponds to the structure given as argument to the startPublishing() method.
        \return \ref CommunicationParameters containing the parameters used to initialize communication with the Fusion Module.
         */
        CommunicationParameters getCommunicationParameters();

        ///@}

        // -----------------------------------------------------------------
        //                         (static)
        // -----------------------------------------------------------------
        /**
        \brief Returns the version of the currently installed ZED SDK.
        \return The ZED SDK version as a string with the following format: MAJOR.MINOR.PATCH

        \code
        std::cout << Camera::getSDKVersion() << std::endl;
        \endcode
         */
        static String getSDKVersion();


        /**
        \brief Returns the version of the currently installed ZED SDK.
        \param major : Major variable of the version filled.
        \param minor : Minor variable of the version filled.
        \param patch : Patch variable of the version filled.

        \code
        int mj_v, mn_v,ptch_v;
        Camera::getSDKVersion(mj_v,mn_v,ptch_v);
        std::cout << "SDK Version v" << mj_v << "." << mn_v << "." << ptch_v << std::endl;
        \endcode

         */
        static void getSDKVersion(int &major, int &minor, int &patch);

        /**
        \brief List all the connected devices with their associated information.

        This method lists all the cameras available and provides their serial number, models and other information.

        \return The device properties for each connected camera.

        \warning As this method returns an std::vector, it is only safe to use in Release or ReleaseWithDebugInfos mode (not Debug).
        \n This is due to a known compatibility issue between release (the SDK) and debug (your app) implementations of std::vector.

         */
        static std::vector<sl::DeviceProperties> getDeviceList();

        /**
        \brief List all the streaming devices with their associated information.

        \return The streaming properties for each connected camera.

        \warning As this method returns an std::vector, it is only safe to use in Release or ReleaseWithDebugInfos mode (not Debug).
        \n This is due to a known compatibility issue between release (the SDK) and debug (your app) implementations of std::vector.
        
        \warning This method takes around 2 seconds to make sure all network informations has been captured. Make sure to run this method in a thread.

         */
        static std::vector<sl::StreamingProperties> getStreamingDeviceList();


        /**
        \brief Performs a hardware reset of the ZED 2 and the ZED 2i.

        \param sn : Serial number of the camera to reset, or 0 to reset the first camera detected.
        \param fullReboot : Perform a full reboot (sensors and video modules) if true, otherwise only the video module will be rebooted.
        \return \ref ERROR_CODE "ERROR_CODE::SUCCESS" if everything went fine.
        \return \ref ERROR_CODE "ERROR_CODE::CAMERA_NOT_DETECTED" if no camera was detected.
        \return \ref ERROR_CODE "ERROR_CODE::FAILURE"  otherwise.
        
        \note This method only works for ZED 2, ZED 2i, and newer camera models.
        \warning This method will invalidate any sl::Camera object, since the device is rebooting.
        \warning Under Windows it is not possible to get exclusive access to HID devices, hence calling this method while the camera is opened by another process will cause it to freeze for a few seconds while the device is rebooting.
         */
        static sl::ERROR_CODE reboot(int sn, bool fullReboot = true);

        /**
        \brief The \ref Camera object cannot be copied. Therfore, its copy constructor is disabled.

        If you need to share a Camera instance across several threads or object, please consider using a pointer.

        \see Camera()
         */
        Camera(const Camera&) = delete;

    private:
        CameraMemberHandler* h = 0;
        bool opened = false;

        //std::mutex gmsl_open_guard;
    };

    /**
    \ingroup Object_group
    \brief Checks if a corresponding optimized engine is found for the requested Model based on your rig configuration.
    \return The status of the given model for the specified GPU.
     */
    AI_Model_status /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ checkAIModelStatus(AI_MODELS model, int gpu_id = 0);

    /**
    \ingroup Object_group
    \brief Downloads the requested model.
    \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if the model is already download.
     */
    ERROR_CODE /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ downloadAIModel(sl::AI_MODELS model, int gpu_id = 0);

    /**
    \ingroup Object_group
    \brief Optimizes the requested model (and download the model if it is not present on the host).
    \return [sl::ERROR_CODE::SUCCESS](\ref ERROR_CODE) if the model is well optimized.
     */
    ERROR_CODE /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ optimizeAIModel(sl::AI_MODELS model, int gpu_id = 0);

    ///@cond SHOWHIDDEN
    String /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ toString(const SpatialMappingParameters::MAPPING_RESOLUTION& resolution);

    inline std::ostream& operator<<(std::ostream& os, const SpatialMappingParameters::MAPPING_RESOLUTION& resolution) {
        return os << toString(resolution);
    }

    String /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ toString(const SpatialMappingParameters::MAPPING_RANGE& range);

    inline std::ostream& operator<<(std::ostream& os, const SpatialMappingParameters::MAPPING_RANGE& range) {
        return os << toString(range);
    }

    String /*@cond SHOWHIDDEN*/SL_SDK_EXPORT/*@endcond*/ toString(const SpatialMappingParameters::SPATIAL_MAP_TYPE& map_type);

    inline std::ostream& operator<<(std::ostream& os, const SpatialMappingParameters::SPATIAL_MAP_TYPE& map_type) {
        return os << toString(map_type);
    }
    ///@endcond

}

#endif /* __CAMERA_HPP__ */
