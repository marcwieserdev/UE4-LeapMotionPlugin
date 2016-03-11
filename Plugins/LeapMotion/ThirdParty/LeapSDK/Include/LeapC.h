/******************************************************************************\
* Copyright (C) 2012-2015 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/
#ifndef _LEAP_C_H
#define _LEAP_C_H

#ifndef LEAP_EXPORT
#  ifdef _MSC_VER
#    define LEAP_EXPORT __declspec(dllimport)
#  else
#    define LEAP_EXPORT
#  endif
#endif

#ifdef _MSC_VER
#  define LEAP_CALL __stdcall
#else
#  define LEAP_CALL
#endif

#if defined(__cplusplus) && __cplusplus >= 201103
#  define LEAP_STATIC_ASSERT static_assert
#else
#  define LEAP_STATIC_ASSERT(x, y)
#endif

#pragma pack(1)

// Define integer types for Visual Studio 2008 and earlier
#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * All return codes reported by the API
 */
enum eLeapRS {
  /**
   * The operation completed successfully
   */
  eLeapRS_Success                       = 0x00000000,

  /**
   * An unknown error has occurred
   */
  eLeapRS_UnknownError                  = 0xE2010000,

  /**
   * An invalid argument was specified
   */
  eLeapRS_InvalidArgument               = 0xE2010001,

  /**
   * Insufficient resources existed to complete the request
   */
  eLeapRS_InsufficientResources         = 0xE2010002,

  /**
   * The specified buffer was not large enough to complete the request
   */
  eLeapRS_InsufficientBuffer            = 0xE2010003,

  /**
   * The requested operation has timed out
   */
  eLeapRS_Timeout                       = 0xE2010004,

  /**
   * Cannot poll on a connection that is not currently connected
   */
  eLeapRS_NotConnected                  = 0xE2010005,

  /**
   * Cannot comply with the requested operation because the client has not completed
   * a server handshake
   */
  eLeapRS_HandshakeIncomplete           = 0xE2010006,

  /**
   * The specified buffer size is too large
   */
  eLeapRS_BufferSizeOverflow            = 0xE2010007,

  /**
   * A communications protocol error has occurred
   */
  eLeapRS_ProtocolError                 = 0xE2010008,

  /**
   * The server incorrectly specified zero as a client ID
   */
  eLeapRS_InvalidClientID               = 0xE2010009,

  /**
   * The connection to the service was unexpectedly closed while reading or writing a message.
   * The server may have crashed.
   */
  eLeapRS_UnexpectedClosed              = 0xE201000A,

  /**
   * The specified request token does not appear to be valid
   *
   * Provided that the token value which identifies the request itself was, at one point, valid, this
   * error condition occurs when the request to which the token refers has already been satisfied or
   * is currently being satisfied.
   */
  eLeapRS_UnknownImageFrameRequest      = 0xE201000B,

  /**
   * A connection could not be established to the Leap Motion service
   */
  eLeapRS_NotAvailable                  = 0xE7010002,

  /**
   * The requested operation can only be performed while the device is streaming
   */
  eLeapRS_NotStreaming                  = 0xE7010004,

  /**
   * The specified device could not be opened.  It is possible that the device identifier
   * is invalid, or that the device has been disconnected since being enumerated.
   */
  eLeapRS_CannotOpenDevice              = 0xE7010005,
};

/**
 * LeapOpenConnection flags
 */
enum eLeapConnectionFlags {
  eLeapConnectionFlags_Default          = 0x00000000,
};

/**
 * Represents a leap connection object
 */
typedef struct _LEAP_CONNECTION *LEAP_CONNECTION;

/**
 * Represents a leap device object
 */
typedef struct _LEAP_DEVICE *LEAP_DEVICE;

/**
 * Represents a calibration object
 */
typedef struct _LEAP_CALIBRATION *LEAP_CALIBRATION;

/**
 * Represents a leap device reference
 *
 * Call LeapOpenDevice to convert this to a LEAP_DEVICE structure
 */
typedef struct _LEAP_DEVICE_REF {
  void* handle;
  uint32_t id;
} LEAP_DEVICE_REF;

/**
 * A leap connection configuration object
 */
typedef struct _LEAP_CONNECTION_CONFIG {
  // Initialized to the size of this structure
  uint32_t size;

  // A collection of eLeapConnectionFlags
  uint32_t flags;

  /**
   * Specifies the server namespace to be used.  Leave NULL to use the default namespace.
   *
   * It is possible to launch the service with a different IPC connection namespace.  Clients
   * wishing to connect to a different server namespace may specify that namespace here.
   *
   * The default connection namespace is "Leap Service".
   */
  const char* server_namespace;
} LEAP_CONNECTION_CONFIG;

/**
 * Samples the universal clock used by the system to timestamp image and tracking frames
 *
 * The returned counter value is given in microseconds since an epoch time.  The clock used for the
 * counter itself is implementation-defined, but generally speaking, it is global, monotonic, and
 * makes use of the most accurate high performance counter available on the system.
 */
LEAP_EXPORT int64_t LEAP_CALL LeapGetNow(void);

/**
 * Creates a new Leap connection object
 *
 * Methods in the dispatch table pointed to by pConfig are invoked synchronously.
 *
 * @param pConfig The configuration to be used with the newly created connection.  If this member is null, a
 *                connection is created with a default configuration.
 * @param phConnection Receives a pointer to the connection object
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapCreateConnection(const LEAP_CONNECTION_CONFIG* pConfig, LEAP_CONNECTION* phConnection);

/**
 * Opens a connection to the service
 *
 * This routine will not block.  A connection to the service will not be established until the first
 * invocation of LeapPollConnection.
 *
 * @param connection A handle to the connection object
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapOpenConnection(LEAP_CONNECTION hConnection);

typedef struct _LEAP_CONNECTION_EVENT {
  // Reserved
  uint32_t flags;
} LEAP_CONNECTION_EVENT;

/**
 * If the client send a message to the server after the connection is lost, calling LeapPollConnection would
 * return with this event immediately;
 * If no messages is sent to the server after the connection is lost, it would take about 5000 milliseconds
 * after the first LeapPollConnection call to receive this event.
 */
typedef struct _LEAP_CONNECTION_LOST_EVENT {
  // Reserved
  uint32_t flags;
} LEAP_CONNECTION_LOST_EVENT;

enum eLeapConnectionStatus {
  // The connection is not currently connected
  // Need to call LeapOpenConnection to open a connection to the server
  eLeapConnectionStatus_NotConnected = 0,

  // A connection has been established
  eLeapConnectionStatus_Connected,

  // The connection handshake has not completed
  eLeapConnectionStatus_HandshakeIncomplete,

  // A connection could not be established because the server does not appear to be running
  eLeapConnectionStatus_NotRunning    = 0xE7030004
};

typedef struct _LEAP_CONNECTION_INFO {
  // The size of this structure
  uint32_t size;

  // The current status of this connection
  eLeapConnectionStatus status;
} LEAP_CONNECTION_INFO;

/**
 * Retrieves status information about the specified connection
 *
 * @param hConnection The connection to query for additional information
 * @param pInfo A pointer to a buffer that receives additional connection information. One input,
 *   the size field of pInfo is the size of the buffer; On output, the size field of pInfo receives
 *   the size necessary to hold the entire information block.
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapGetConnectionInfo(LEAP_CONNECTION hConnection, LEAP_CONNECTION_INFO* pInfo);

enum eLeapValueType {
  eLeapValueType_Unknown,
  eLeapValueType_Boolean,
  eLeapValueType_Int32,
  eleapValueType_Float,
  eLeapValueType_String,
  FORCE_DWORD = 0x7FFFFFFF
};
LEAP_STATIC_ASSERT(sizeof(eLeapValueType) == 4, "Incorrect enum size");

typedef struct _LEAP_VARIANT {
  eLeapValueType type;
  union {
    bool boolValue;
    int32_t iValue;
    float fValue;
    const char* strValue;
  };
} LEAP_VARIANT;

typedef struct _LEAP_CONFIG_RESPONSE_EVENT {
  uint32_t requestID;

  // The value retrieved by the server.  The user must not attempt to free any memory pointed to by
  // this member.  The value held here is only valid until the next call to LeapPollConnection.
  LEAP_VARIANT value;
} LEAP_CONFIG_RESPONSE_EVENT;

typedef struct _LEAP_CONFIG_CHANGE_EVENT {
  uint32_t requestID;

  // The status of the commit operation, true on succeess, false on failure
  bool status;
} LEAP_CONFIG_CHANGE_EVENT;

/**
 * Causes the client to commit the configuration change to the server
 *
 * @param hConnection A handle to the connection object
 * @param key The key of the configuration to commit
 * @param value The value of the configuration to commit
 * @param pRequestID A pointer that receives the id for this request, the server will respond the commit operation status with this id
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapSaveConfigValue(LEAP_CONNECTION hConnection, const char* key, const LEAP_VARIANT* value, uint32_t* pRequestID);

/**
 * Causes the client to send a request for the specified configuration value to the server
 *
 * @param hConnection A handle to the connection object
 * @param key The key of the configuration to request
 * @param pRequestID A pointer that receives the id for this request, the server will respond the configuration value with this id
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapRequestConfigValue(LEAP_CONNECTION hConnection, const char* key, uint32_t* pRequestID);

/**
 * Retrieves a list of devices currently attached to the system
 *
 * @param hConnection A handle to the connection object
 * @param pArray A pointer to an array that is filled with the device list
 * @param pnArray On input, the number of elements in pArray; on output, the number of valid handles
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapGetDeviceList(LEAP_CONNECTION hConnection, LEAP_DEVICE_REF* pArray, uint32_t* pnArray);

/**
 * Opens a device reference and retreives a handle
 *
 * To ensure resources are properly freed, users must call LeapCloseDevice on the returned handle
 * for any successful call, even if the retrieved device has problems or cannot stream.
 *
 * @param rDevice A device reference
 * @param phDevice A pointer that receives the opened device handle
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapOpenDevice(LEAP_DEVICE_REF rDevice, LEAP_DEVICE* phDevice);

enum eLeapDeviceCaps {
  // The device can send color images
  eLeapDeviceCaps_Color      = 0x00000001,

  // The device is embedded in another piece of hardware, such as a keyboard or laptop
  eLeapDeviceCaps_Embedded   = 0x00010000
};

enum eLeapDeviceType {
  // The Leap Motion consumer peripheral
  eLeapDeviceType_Peripheral      = 0x0003,

  // HOPS/PONGO Legacy device
  eLeapDeviceType_Legacy          = 0x1001,

  // Leap Motion HOPS Keyboard
  eLeapDeviceType_Hops            = 0x1002,

  // Leap Motion Pongo laptop-embedded device
  eLeapDeviceType_Pongo           = 0x1003,

  // Internal research product codename "Dragonfly"
  eLeapDeviceType_Dragonfly       = 0x1102,

  // Internal research product codename "Nightcrawler"
  eLeapDeviceType_Nightcrawler    = 0x1201
};

/**
 * A structure that provides extended information about a Leap device
 **/
typedef struct _LEAP_DEVICE_INFO {
  // Size of this structure
  uint32_t size;

  // A combination of eLeapDeviceStatus flags
  uint32_t status;

  // A combination of eLeapDeviceCaps flags
  uint32_t caps;

  // One of the LEAP_DEVICE_TYPE members
  eLeapDeviceType type;

  /**
   * The device baseline, in micrometers
   *
   * The baseline is defined as the distance between the center axis of each lens in a stereo camera
   * system.  For other camera systems, this value is set to zero.
   */
  uint32_t baseline;

  // Maximum length of the DeviceSerial buffer
  uint32_t serial_length;

  // A pointer to the null-terminated device serial number string
  char* serial;

  // The horizontal field of view of this device
  float h_fov;

  // The vertical field of view of this device
  float v_fov;

  // The maximum range for this device, in micrometers
  uint32_t range;
} LEAP_DEVICE_INFO;

/**
 * Gets additional information about the specified device
 *
 * The caller is responsible for assigning DeviceSerial to a caller-allocated buffer large enough to
 * receive the device serial number.
 *
 * On return, the value of serial_length will be set to the minimum buffer size required to receive
 * the serial number, regardless of whether serial contains a valid pointer to memory.
 *
 * @param device A handle to the device to be queried
 * @param info Extended information about the specified device
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapGetDeviceInfo(LEAP_DEVICE hDevice, LEAP_DEVICE_INFO* info);

enum eLeapPolicyFlag {
  // Allows frame receipt even when this application is not the foreground application
  eLeapPolicyFlag_BackgroundFrames = 0x00000001,

  // Optimize tracking for head-mounted device
  eLeapPolicyFlag_OptimizeHMD      = 0x00000004,

  // Modifies the security token to allow calls to LeapPauseDevice to succeed
  eLeapPolicyFlag_AllowPauseResume = 0x00000008,
};

typedef struct _LEAP_POLICY_EVENT {
  // Reserved
  uint32_t reserved;

  // The policy effective on this connection as of the time the event was processed
  uint32_t current_policy;
} LEAP_POLICY_EVENT;

/**
 * Sets policy flags associated with the specified connection
 *
 * To get the current policy, specify zero for both set and clear, this method will not change any flags, and
 * the LEAP_POLICY_EVENT will have the current policy.
 *
 * @param hConnection The connection to be modified
 * @param set A combination of flags to be set
 * @param clear A combination of flags to be cleared
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapSetPolicyFlags(LEAP_CONNECTION hConnection, uint64_t set, uint64_t clear);

enum eLeapDeviceFlag {
  /**
   * Flag set if the device is presently streaming frames
   *
   * This flag is updated when the user pauses or resumes tracking on the device from the Leap control
   * panel.  Modification of this flag will fail if the AllowPauseResume policy is not set on this device
   * object.
   */
  eLeapDeviceFlag_Stream                = 0x00000001
};

/**
 * Sets flags associated with the specified device
 *
 * If zero is specified for both set and clear, this method will not change any flags, and will report
 * currently assigned flags via prior, if prior is non-null.
 *
 * @param device The device to be modified
 * @param set A combination of flags to be set
 * @param clear A combination of flags to be cleared
 * @param prior An optional pointer to an integer that receives the flags previously set on the device
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapSetDeviceFlags(LEAP_DEVICE hDevice, uint64_t set, uint64_t clear, uint64_t* prior);

typedef struct _LEAP_DEVICE_EVENT {
  // Reserved
  uint32_t flags;

  // The handle reference of to the newly attached device
  LEAP_DEVICE_REF device;
} LEAP_DEVICE_EVENT;

enum eLeapDeviceStatus {
  // Presently sending frames to all clients that have requested them
  eLeapDeviceStatus_Streaming      = 0x00000001,

  // Device streaming has been paused
  eLeapDeviceStatus_Paused         = 0x00000002,

  // The device has failed, but the failure reason is not known
  eLeapDeviceStatus_UnknownFailure = 0xE8010000,

  // Bad calibration, cannot send frames
  eLeapDeviceStatus_BadCalibration = 0xE8010001,

  // Corrupt firmware and/or cannot receive a required firmware update
  eLeapDeviceStatus_BadFirmware    = 0xE8010002,

  // Exhibiting USB communications issues
  eLeapDeviceStatus_BadTransport   = 0xE8010003,

  // Missing critical control interfaces needed for communication
  eLeapDeviceStatus_BadControl     = 0xE8010004,
};

typedef struct _LEAP_DEVICE_FAILURE_EVENT {
  /**
   * The status of this failure event
   */
  eLeapDeviceStatus status;

  /**
   * A handle to the device generating this event, if available, otherwise NULL
   *
   * The user is not responsible for closing this handle.
   */
  LEAP_DEVICE hDevice;
} LEAP_DEVICE_FAILURE_EVENT;

typedef struct _LEAP_FRAME_HEADER {
  /**
   * Reserved, set to zero
   */
  void* reserved;

  /**
   * A unique identifier for this frame
   *
   * All frames carrying this frame ID are part of the same unit of processing.  This counter
   * is generally an increasing counter, but may reset to another value if the user stops and
   * restarts streaming.
   */
  int64_t frame_id;

  /**
   * The timestamp for this image, in microseconds, referenced against LeapGetNow
   */
  int64_t timestamp;
} LEAP_FRAME_HEADER;

enum eLeapImageType {
  // Invalid/unknown type
  eLeapImageType_UNKOWN = 0,

  // Default processed IR images
  eLeapImageType_Default,

  // Raw images from the device
  eLeapImageType_Raw
};

enum eLeapImageFormat {
  // Invalid/unknown format
  eLeapImageFormat_UNKNOWN = 0,

  // An infrared image
  eLeapImageFormat_IR = 0x317249,

  // A Bayer RGBIr image with uncorrected RGB channels
  eLeapImageFormat_RGBIr_Bayer = 0x49425247,
};

enum eLeapPerspectiveType {
  // Reserved, invalid
  eLeapPerspectiveType_invalid = 0,

  // A canonically left image
  eLeapPerspectiveType_stereo_left = 1,

  // A canonically right image
  eLeapPerspectiveType_stereo_right = 2,

  // Reserved for future use
  eLeapPerspectiveType_mono = 3,
};

typedef struct _LEAP_IMAGE_PROPERTIES {
  // The type of this image
  eLeapImageType type;

  // The format of this image
  eLeapImageFormat format;

  // Number of bits per pixel
  uint32_t bpp;

  // Number of horizontal pixels in the image
  uint32_t width;

  // Number of rows of pixels in the image
  uint32_t height;

  // Aspect ratio values, reflects the scaling values given for the X and Y axes:
  float x_scale;
  float y_scale;

  // Offset values
  float x_offset;
  float y_offset;
} LEAP_IMAGE_PROPERTIES;

#define LEAP_DISTORTION_MATRIX_N 64
typedef struct _LEAP_DISTORTION_MATRIX {
  struct {
    float x;
    float y;
  } matrix[LEAP_DISTORTION_MATRIX_N][LEAP_DISTORTION_MATRIX_N];
} LEAP_DISTORTION_MATRIX;

typedef struct _LEAP_IMAGE_FRAME_REQUEST_TOKEN {
  /**
   * The ID of the request that was sent up to the service.  This ID is not reused and should be
   * treated as an opaque value
   */
  uint32_t requestID;
} LEAP_IMAGE_FRAME_REQUEST_TOKEN;

typedef struct _LEAP_IMAGE_COMPLETE_EVENT {
  /**
   * A token which identifies the corresponding request
   */
  LEAP_IMAGE_FRAME_REQUEST_TOKEN token;

  // Universal frame information header
  LEAP_FRAME_HEADER info;

  // A pointer to the properties of the received image
  const LEAP_IMAGE_PROPERTIES* properties;

  /**
   * A version number for the distortion matrix.  When the distortion matrix
   * changes, this number is updated.  This number is guaranteed not to repeat
   * for the lifetime of the connection.
   *
   * This version number is also guaranteed to be distinct for each perspective
   * of an image.
   *
   * This value is guaranteed to be nonzero if it is valid
   */
  uint64_t matrix_version;

  // A handle to the calibration structure for the image
  LEAP_CALIBRATION calib;

  // The pointers to the left and right distortion matrix
  LEAP_DISTORTION_MATRIX* distortion_matrix[2];

  /**
   * The buffer the user specified in LeapRequestImages.
   */
  void* pfnData;

  /**
   * The number of bytes written to the buffer pointed to by pfnData.
   */
  uint64_t data_written;
} LEAP_IMAGE_COMPLETE_EVENT;

typedef struct _LEAP_IMAGE_FRAME_DESCRIPTION {
  /**
   * The ID of the frame corresponding to the requested image
   */
  int64_t frame_id;

  /**
   * The type of the image being requested
   */
  eLeapImageType type;

  /**
   * Length of the buffer pointed to by pBuffer
   */
  uint64_t buffer_len;

  /**
   * The user-specified buffer where the images in the frame will be stored
   */
  void* pBuffer;
} LEAP_IMAGE_FRAME_DESCRIPTION;

enum eLeapImageRequestError {
  /*
   * An unkown error has occured
   */
  eLeapImageRequestError_Unknown,

  /*
   * The config 'image_mode' is set to 0 disallow
   */
  eLeapImageRequestError_ImagesDisabled,

  /*
   * The requested images are not available
   */
  eLeapImageRequestError_Unavailable,

  /*
   * The provided buffer is not large enough for the requested images
   */
  eLeapImageRequestError_InsufficientBuffer,
};

typedef struct _LEAP_IMAGE_FRAME_REQUEST_ERROR_EVENT {
  /**
   * A token which identifies the corresponding request
   */
  LEAP_IMAGE_FRAME_REQUEST_TOKEN token;

  /**
   * The error message causing the image request operation to fail
   **/
  eLeapImageRequestError error;

  /*
   * If the error is eLeapImageRequestError_InsufficientBuffer,
   * this will specify the required minimum buffer size for the requested image data
   */
  uint64_t required_buffer_len;

  /**
   * A copy of the image frame description supplied in the request
   */
  LEAP_IMAGE_FRAME_DESCRIPTION description;
} LEAP_IMAGE_FRAME_REQUEST_ERROR_EVENT;

/**
 * Causes the client to send a request for the specified images to the server
 *
 * @param hConnection A handle to the connection object
 * @param pDescription A pointer to a LEAP_IMAGE_DESCRIPTION struct which describes which images to request
 * @param pToken A pointer to a frame request token which may be used later to cancel or request information
 *        about the request
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapRequestImages(LEAP_CONNECTION hConnection, const LEAP_IMAGE_FRAME_DESCRIPTION* pdescription, LEAP_IMAGE_FRAME_REQUEST_TOKEN* pToken);

typedef enum _eLeapImageFrameRequestStatus {
  // The request is still being serviced by the server
  eLeapImageFrameRequestStatus_Waiting,

  // The request is currently being received by the application
  eLeapImageFrameRequestStatus_Underway,

  // The request is being cancelled by the user
  eLeapImageFrameRequestStatus_Cancelling
} eLeapImageFrameRequestStatus;

/**
 * Retrieves status information about a currently in-flight image request
 *
 * @param hConnection The previously connected connection object
 * @param token A token previously returned by LeapRequestImages
 * @param pStatus Receives current status of the request
 **/
LEAP_EXPORT eLeapRS LEAP_CALL LeapGetImageRequestStatus(LEAP_CONNECTION hConnection, LEAP_IMAGE_FRAME_REQUEST_TOKEN token, eLeapImageFrameRequestStatus* pStatus);

/**
 * Cancels a images request identified by the token returned by a prior call to LeapRequestImages
 *
 * @param hConnection A handle to the connection object
 * @param token A token returned by a prior call to LeapRequestImages
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapCancelImageFrameRequest(LEAP_CONNECTION hConnection, LEAP_IMAGE_FRAME_REQUEST_TOKEN token);

typedef struct _LEAP_VECTOR {
  union {
    float v[3];
    struct {
      float x;
      float y;
      float z;
    };
  };
} LEAP_VECTOR;

typedef struct _LEAP_MATRIX {
  LEAP_VECTOR cols[3];
} LEAP_MATRIX;

typedef struct _LEAP_BONE {
  // The base of the bone, closer to the heart.
  LEAP_VECTOR prev_joint;

  // The end of the bone, further from the heart.
  LEAP_VECTOR next_joint;

  // The average width of the flesh around the bone in millimeters.
  float width;

  // Basis matrix for this bone
  LEAP_MATRIX basis;
} LEAP_BONE;

typedef struct _LEAP_DIGIT {
  // The identifier of this finger
  int32_t finger_id;

  union {
    // All bones as an iterable collection
    LEAP_BONE bones[4];

    struct {
      // The part of the finger bone inside the palm
      LEAP_BONE metacarpal;

      // The bone closest to the knuckle, on the outside of the palm
      LEAP_BONE proximal;

      // The bone between the Proximal bone and the fingertip.  Thumbs do not
      // have an intermediate bone; for thumbs, this bone has zero length and
      // width, an identity basis matrix, and its joint positions are equal.
      LEAP_BONE intermediate;

      // The fingertip
      LEAP_BONE distal;
    };
  };

  // Instantaneous finger tip speed
  LEAP_VECTOR tip_velocity;

  // Filtered tip position
  LEAP_VECTOR stabilized_tip_position;

  // Whether finger is straight
  uint32_t is_extended;
} LEAP_DIGIT;

typedef struct _LEAP_PALM {
  /**
   * The center position of the palm in millimeters from the Leap Motion Controller origin.
   */
  LEAP_VECTOR position;

  /**
   * The stabilized palm position of this Hand.
   *
   * Smoothing and stabilization is performed in order to make
   * this value more suitable for interaction with 2D content. The stabilized
   * position lags behind the palm position by a variable amount, depending
   * primarily on the speed of movement.
   */
  LEAP_VECTOR stabilized_position;

  /**
   * The rate of change of the palm position in millimeters/second.
   */
  LEAP_VECTOR velocity;

  /**
   * The normal vector to the palm. If your hand is flat, this vector will
   * point downward, or "out" of the front surface of your palm.
   */
  LEAP_VECTOR normal;

  /**
   * The estimated width of the palm when the hand is in a flat position.
   */
  float width;

  /**
   * The direction from the palm position toward the fingers.
   */
  LEAP_VECTOR direction;
} LEAP_PALM;

enum eLeapHandType {
  // Left hand
  eLeapHandType_Left,

  // Right hand
  eLeapHandType_Right
};

typedef struct _LEAP_HAND {
  /**
   * Unique ID for hand across frames.
   */
  uint32_t id;

  /**
   * Reserved
   */
  uint32_t flags;

  /**
   * Identifies the type of this hand
   */
  eLeapHandType type;

  /**
   * How confident we are with a given hand pose.
   */
  float confidence;

  /**
   * The total amount of time this hand has been visible, in microseconds.
   */
  uint64_t visible_time;

  /**
   * The distance between index finger and thumb when pinching.
   */
  float pinch_distance;

  /**
   * The average angle of fingers to palm when grabbing.
   */
  float grab_angle;

  /**
   * The holding strength of a pinch hand pose.
   */
  float pinch_strength;

  /**
   * The strength of a grab hand pose.
   */
  float grab_strength;

  /**
   * Extra information about the palm.
   */
  LEAP_PALM* palm;

  // Fingers on this hand
  union {
    struct {
      const LEAP_DIGIT* thumb;
      const LEAP_DIGIT* index;
      const LEAP_DIGIT* middle;
      const LEAP_DIGIT* ring;
      const LEAP_DIGIT* pinky;
    };
    const LEAP_DIGIT* digits[5];
  };

  /**
   * The arm to which this hand is attached.
   */
  LEAP_BONE* arm;
} LEAP_HAND;

typedef struct _LEAP_TRACKING_EVENT {
  // Universal frame information header
  LEAP_FRAME_HEADER info;

  /**
   * An identifier for this tracking frame.  This identifier is meant to be monotonically
   * increasing, but values may be skipped if the client application does not dispatch messages
   * fast enough.  This number also generally increases at the same rate as info.frame_id, but
   * if the server cannot process every image, the frame identifier may increase faster.
   */
  int64_t tracking_frame_id;

  // Height, width, and depth of an interaction box
  LEAP_VECTOR interaction_box_size;

  // Center point of the interaction box
  LEAP_VECTOR interaction_box_center;

  // The number of hands pointed to by pHands
  uint32_t nHands;

  // A pointer to an array of hands
  const LEAP_HAND* pHands;

  /**
   * Current tracking frame rate in hertz
   *
   * This frame rate is distinct from the image frame rate, which is the rate that images are
   * being read from the device.  Depending on host CPU limitations, the tracking frame rate
   * may be substantially less than the device frame rate.
   *
   * This number is generally equal to or less than the device frame rate, but there is one
   * case where this number may be _higher_ than the device frame rate:  When the device rate
   * drops.  In this case, the device frame rate will fall sooner than the tracking frame rate.
   *
   * This number is equal to zero if there are not enough frames to estimate frame rate.
   *
   * This number cannot be negative.
   */
  float framerate;
} LEAP_TRACKING_EVENT;

typedef struct _LEAP_TRACKED_QUAD_EVENT {
  // Universal frame information header
  LEAP_FRAME_HEADER info;

  // Width and height of this quad
  float width;
  float height;

  // The horizontal resolution of the quad display area in pixels.
  int32_t resolutionX;

  // The vertical resolution of the quad display area in pixels.
  int32_t resolutionY;

  // Reports whether the quad is currently detected within the Leap Motion field of view.
  uint32_t visible;

  /**
   * The position of the center of the quad display area within the Leap Motion frame of reference.
   *
   * In millimeters.
   */
  LEAP_VECTOR position;

  // The orientation of the quad within the Leap Motion frame of reference.
  LEAP_MATRIX orientation;
} LEAP_TRACKED_QUAD_EVENT;

enum eLeapLogSeverity {
  eLeapLogSeverity_Unknown = 0,
  eLeapLogSeverity_Critical,
  eLeapLogSeverity_Warning,
  eLeapLogSeverity_Information
};

typedef struct _LEAP_LOG_EVENT {
  eLeapLogSeverity Severity;
  int64_t Timestamp;
  // A pointer to a null-terminated string containing the current log message
  const char* Message;
} LEAP_LOG_EVENT;

enum eLeapEventType {
  /**
   * No event occurred in the specified timeout period
   */
  eLeapEventType_None = 0,

  /**
   * A connection event has occurred
   */
  eLeapEventType_Connection,

  /**
   * The connection with the service has been lost
   */
  eLeapEventType_ConnectionLost,

  /**
   * A device event has occurred
   */
  eLeapEventType_Device,

  /**
   * A device failure event has occurred
   */
  eLeapEventType_DeviceFailure,

  /**
   * A policy event has occurred due to setting policy request or certain config changes
   * - images_mode, background_app_mode
   */
  eLeapEventType_Policy,

  /**
   * A tracking frame has been received
   */
  eLeapEventType_Tracking = 0x100,

  /**
   * An error has occured for a image request,
   * the client will not receive the requested images
   */
  eLeapEventType_ImageRequestError,

  /**
  * The underlying transport has finished reading an image
  */
  eLeapEventType_ImageComplete,

  /**
   * A new tracked quad has been received
   */
  eLeapEventType_TrackedQuad,

  /**
   * A log event has occured
   */
  eLeapEventType_LogEvent,

  /**
   * Event asserted when the underlying device object has been lost
   *
   * This event type will always be asserted regardless of the user flags assignment.  Users are
   * required to correctly handle this event when it is received.
   *
   * This event is generally asserted when the device has been detached from the system, when the
   * connection to the service has been lost, or if the device is closed while streaming.  Generally,
   * any event where the system can conclude no further frames will be received will cause this
   * method to be invoked.
   */
  eLeapEventType_DeviceLost,

  /**
   * A response to the config request has been received
   */
  eLeapEventType_ConfigResponse,

  /**
   * The config has been committed
   */
  eLeapEventType_ConfigChange
};

typedef struct _LEAP_CONNECTION_MESSAGE {
  /**
   * The size of this structure
   */
  uint32_t size;

  /**
   * The type of the retrieved event
   */
  eLeapEventType type;

  /**
   * A pointer to the event data proper
   */
  union {
    const void* pointer;
    const LEAP_CONNECTION_EVENT* connection_event;
    const LEAP_CONNECTION_LOST_EVENT* connection_lost_event;
    const LEAP_DEVICE_EVENT* device_event;
    const LEAP_POLICY_EVENT* policy_event;
    const LEAP_DEVICE_FAILURE_EVENT* device_failure_event;
    const LEAP_TRACKING_EVENT* tracking_event;
    const LEAP_IMAGE_FRAME_REQUEST_ERROR_EVENT* image_request_error_event;
    const LEAP_IMAGE_COMPLETE_EVENT* image_complete_event;
    const LEAP_TRACKED_QUAD_EVENT* tracked_quad_event;
    const LEAP_LOG_EVENT* log_event;
    const LEAP_CONFIG_RESPONSE_EVENT* config_response_event;
    const LEAP_CONFIG_CHANGE_EVENT* config_change_event;
  };
} LEAP_CONNECTION_MESSAGE;

/**
 * Polls the connection for a new event
 *
 * The specific types of events that may be recieved are not configurable in this entrypoint.  Configure
 * the device or connection object directly to change what events will be received.
 *
 * Pointers in the retrieved evt structure will be valid until the associated connection or device is
 * closed, or the next call to LeapPollConnection.
 *
 * @param hConnection A handle to the connection object
 * @param timeout The maximum amount of time to wait, in milliseconds.  If this value is zero,
 * this method will return what is currently available, if anything, and will not block.
 * @param evt A pointer to a structure that is filled with event information.  This structure will be valid
 * as long as the LEAP_CONNECTION object is valid.
 *
 * @returns An appropriate error code.  If the operation times out, this method will return
 * eLeapRS_Timeout
 */
LEAP_EXPORT eLeapRS LEAP_CALL LeapPollConnection(LEAP_CONNECTION hConnection, uint32_t timeout, LEAP_CONNECTION_MESSAGE* evt);

/**
 * Closes a device handle previously opened with LeapOpenDevice
 *
 * @param pDevice The device handle to close
 */
LEAP_EXPORT void LEAP_CALL LeapCloseDevice(LEAP_DEVICE hDevice);

/**
 * Closes a previously opened connection
 *
 * This method closes the specified connection object if it is opened, destroys the underlying
 * object, and releases all resources associated with it.
 *
 * This method never fails.
 *
 * @param connection A handle to the connection object to be destroyed
 */
LEAP_EXPORT void LEAP_CALL LeapDestroyConnection(LEAP_CONNECTION hConnection);

#ifdef __cplusplus
}
#endif

#pragma pack()

#endif
