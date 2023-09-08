#ifndef	_MDASLIBTYPES_H_
#define	_MDASLIBTYPES_H_

#ifndef	M_EXPORTS
	#if ( defined _WIN32 || defined _WIN64 ) && !defined WINCE
		#ifdef	M_LIB_EXPORTS
			#define	M_EXPORTS	__declspec(dllexport)
		#else
			#define	M_EXPORTS	__declspec(dllimport)
		#endif
	#else
			#define	M_EXPORTS
	#endif
#endif

#ifndef	M_EXTERN_C
	#ifdef	__cplusplus
		#define	M_EXTERN_C	extern "C"
	#else
		#define	M_EXTERN_C
	#endif
#endif

#ifndef	M_API
	#define	M_API	M_EXPORTS
#endif

#ifndef	BOOL
	typedef int		BOOL;
#endif

#if defined _WIN32 || defined _WIN64 || defined __linux__ || defined dm8147
	#ifndef	NULL
		#ifdef	__cplusplus
			#define	NULL	0
		#else
			#define	((void *)0)
		#endif
	#endif
	
/*
	#ifndef	TRUE
		#define	TRUE	1
	#endif
	#ifndef	FALSE
		#define	FALSE	0
	#endif
*/

#endif


enum eErrorList
{
	ERR_OK = 0,

	ERR_MDAS_ALLOC_FAILURE = 100,
	ERR_MDAS_INPUTIMAGE_WAITING,
	ERR_MDAS_INPUTIMAGE_FRAMEBUFFER,
	ERR_MDAS_INPUTIMAGE_SKIPPING,
	ERR_MDAS_INPUTIMAGE_TIMELIMIT,
	ERR_MDAS_CAMERA_TILTANGLE_INVALID,
	ERR_MDAS_CAMERA_ID_INVALID,

	ERR_LDW_NOTSUPPORT = 200,
	ERR_LDW_ALLOC_FAILURE,

	ERR_FCW_NOTSUPPORT = 400,
	ERR_FCW_ALLOC_FAILURE,

	ERR_PCW_NOTSUPPORT = 500,
	ERR_PCW_ALLOC_FAILURE,

	ERR_SCENE_NOTSUPPORT = 600,
	ERR_SCENE_ALLOC_FAILURE,

	ERR_ACL_NOTSUPPORT = 700,
	ERR_ACL_ALLOC_FAILURE,

	ERR_MCL_NOTSUPPORT = 700,
	ERR_MCL_ALLOC_FAILURE
};

enum eAlgorithm
{
	ALG_LDW	= 0x0001,
	ALG_FCW	= 0x0004,
	ALG_PCW	= 0x0008,
	ALG_ACL	= 0x0100,
	ALG_MCL	= 0x0200
};

enum eImageFormat
{
	IF_YUV422_YUYV = 0,	// YUYVYUYV
	IF_YUV422_UYVY,		// UYVYUYVY
	IF_YUV422_YVYU,		// YVYUYVYU
	IF_YUV422_VYUY,		// VYUYVYUY
	IF_YUV420_IYUV,		// (Y)(U)(V)	Planar, I420
	IF_YUV420_YV12,		// (Y)(V)(U)	Planar
	IF_YUV420_NV12,		// (Y)(UV)		Semi-planar
	IF_YUV420_NV21,		// (Y)(VU)		Semi-planar
	IF_MAX
};

enum eVehicleCAN
{
	VC_VELOCITY_MASK	= 0x0000FFFF,
	VC_TURNSIGNAL_LEFT	= 0x00010000,
	VC_TURNSIGNAL_RIGHT	= 0x00020000,
	VC_HEADLIGHT_ON		= 0x00100000,
	VC_BREAK			= 0x01000000
};

enum eResultFlag
{
	ALARM_LDW_DEPARTURE			= 0x00000001,
	ALARM_FCW_COLLISION_CAUTION	= 0x00000002,
	ALARM_FCW_COLLISION_ALERT	= 0x00000004,
	ALARM_FCW_COLLISION_SERIOUS	= 0x00000008,
	ALARM_FCW_FORWARD_NEAR		= 0x00000010,
	ALARM_FCW_FORWARD_START		= 0x00000020,

	LDW_DEPARTURE_LEFT			= 0x00010000,
	LDW_DEPARTURE_RIGHT			= 0x00020000,

	LDW_CAL_UPDATE_RESULT       = 0x00000001,
	LDW_CAL_APPLY_IMMEDIATELY   = 0x00000002,
	LDW_CAL_APPLIED             = 0x00000010,

	FCW_COLLISION_CAUTION		= 0x00010000,
	FCW_COLLISION_DANGER		= 0x00020000,

	FCW_ALERT_ALARM_ONCE        = 0x00000001,
	FCW_ALERT_ALARM_CONTINUE1   = 0x00000002,		// ttc less than ttc2 & distance at t less than distance at t-1
	FCW_ALERT_ALARM_CONTINUE2   = 0x00000004,		// ttc less than ttc2 & ttc at t less than ttc at t-1
	FCW_ALERT_ALARM_CONTINUE3   = 0x00000008,		// ttc less than ttc2
	FCW_SERIOUS_ALARM_ONCE      = 0x00010000,
	FCW_SERIOUS_ALARM_CONTINUE  = 0x00020000,

	SCENE_DAY					= 0x00000001,
	SCENE_NIGHT					= 0x00000002,
	SCENE_BRIGHT				= 0x00000010,
	SCENE_DARK					= 0x00000020,

	ACL_COMPLETE_HOOD			= 0x00000001,
	ACL_COMPLETE_ANGLE			= 0x00000002,
	ACL_FAIL_HOOD				= 0x00000010,
	ACL_FAIL_ANGLE				= 0x00000020,

	MCL_COMPLETE				= 0x00000001,
	MCL_FAIL					= 0x00000002,
	MCL_FAIL_BADIMAGE			= 0x00000010,
	MCL_FAIL_BIGSTDDEV			= 0x00000020,
	MCL_FAIL_OUTOFRANGE			= 0x00000040
};

typedef struct _ResultScene
{
	unsigned int	resultFlags;					// SCENE_NIGHT ~ SCENE_DARK
} sResultScene;

#define	RESULT_LANEPT_MAX	9
typedef struct _ResultLane
{
	short			reliability;
	short			distance;
	short			count1, count2;
	short			sx1[RESULT_LANEPT_MAX], sy1[RESULT_LANEPT_MAX];
	short			ex1[RESULT_LANEPT_MAX], ey1[RESULT_LANEPT_MAX];
	short			sx2[RESULT_LANEPT_MAX], sy2[RESULT_LANEPT_MAX];
	short			ex2[RESULT_LANEPT_MAX], ey2[RESULT_LANEPT_MAX];
} sResultLane;

typedef struct _ResultLDW
{
	unsigned int	resultFlags;					// LDW_DEPARTURE_LEFT ~ LANE_DEPARTURE_RIGHT, ALARM_LDW_DEPARTURE
	sResultLane		lanes[2];						// 0:left, 1:right
	unsigned short	autoCalFlags;					//LDW_CAL_UPDATE_RESULT ~ LDW_CAL_APPLIED
	short			autoCalVanishLine;
} sResultLDW;

#define	RESULT_VEHICLE_MAX	16
typedef struct _ResultFCW
{
	unsigned int	resultFlags;					// FCW_COLLISION_WARNING, ALARM_FCW_COLLISION_CAUTION ~ ALARM_FCW_FORWARD_START
	char			count;
	char			forwardVehicle;
	short			forwardVehicleTTC;
	short			x[RESULT_VEHICLE_MAX];
	short			y[RESULT_VEHICLE_MAX];
	short			w[RESULT_VEHICLE_MAX];
	short			h[RESULT_VEHICLE_MAX];
	unsigned short	distance[RESULT_VEHICLE_MAX];
} sResultFCW;

typedef struct _ResultPCW
{
	unsigned int	resultFlags;
} sResultPCW;

typedef struct _ResultACL
{
	unsigned int	resultFlags;
	int				hoodLine;
	double			tiltAngle;
} sResultACL;

typedef struct _ResultMCL
{
	unsigned int	resultFlags;
	double			tiltAngle;
	double			yawAngle;
	int				cameraHeight;
} sResultMCL;

typedef void (*pNotifyComplete)(void);

// Functions for DSP
typedef void (*pRequestSubProcRun)(void);

#endif	// _MDASLIBTYPES_H_
