#ifndef	_MDASLIB_H_
#define	_MDASLIB_H_

#include "MDASLibTypes.h"

M_EXTERN_C M_API unsigned int M_GetLastErrorCode();
M_EXTERN_C M_API unsigned int M_GetLastErrorData();

M_EXTERN_C M_API char* M_GetVersion();
M_EXTERN_C M_API BOOL M_Initialize( unsigned int uiActiveFlags, unsigned int uiAsyncFlags );	// eAlgorithm

M_EXTERN_C M_API void M_SetCamera_ID( unsigned int uiID );
M_EXTERN_C M_API void M_SetCamera_SensorUnitPixelSize( double dWidth, double dHeight );			// §­
M_EXTERN_C M_API void M_SetCamera_SensorDownscale( double dDownscale );
M_EXTERN_C M_API void M_SetCamera_LensEFL( double dEFL );										// §®
M_EXTERN_C M_API void M_SetCamera_InputImageFormat( int iFormat );
M_EXTERN_C M_API void M_SetCamera_InputFPS( double dFPS );
M_EXTERN_C M_API void M_SetCamera_CameraImageSize( int iWidth, int iHeight );
M_EXTERN_C M_API void M_SetCamera_CropImageSize( int iLeft, int iTop, int iWidth, int iHeight );
M_EXTERN_C M_API int M_GetCamera_CropImageLeft();
M_EXTERN_C M_API int M_GetCamera_CropImageTop();
M_EXTERN_C M_API void M_SetCamera_InputImageSize( int iWidth, int iHeight );
M_EXTERN_C M_API void M_SetCamera_HeightFromGround( int iHeight );								// §¯
M_EXTERN_C M_API int M_GetCamera_HeightFromGround();
M_EXTERN_C M_API void M_SetCamera_CenterArrangement( int iOffset );								// §¯
M_EXTERN_C M_API int M_GetCamera_CenterArrangement();
M_EXTERN_C M_API void M_SetCamera_TiltedAngle( double dAngle );									// degree
M_EXTERN_C M_API double M_GetCamera_TiltedAngle();
M_EXTERN_C M_API void M_SetCamera_VerticalVanishLine( int iVanishLineX );						// pixel

M_EXTERN_C M_API int M_GetCalib_HorzVanishLine();
M_EXTERN_C M_API int M_GetCalib_VertVanishLine();
M_EXTERN_C M_API int M_GetCalib_CalcHorzVanishLine( double dTiltedAngle );						// degree
M_EXTERN_C M_API double M_GetCalib_CalcTiltedAngle( int iVanishLineY );							// pixel

M_EXTERN_C M_API void M_SetVehicle_Width( int iWidth );
M_EXTERN_C M_API int M_GetVehicle_Width();
M_EXTERN_C M_API void M_SetVehicle_Cam2WheelLength( int iLength );								// §¯
M_EXTERN_C M_API int M_GetVehicle_Cam2WheelLength();
M_EXTERN_C M_API void M_SetVehicle_Cam2BumperLength( int iLength );								// §¯
M_EXTERN_C M_API int M_GetVehicle_Cam2BumperLength();
M_EXTERN_C M_API void M_SetVehicle_HoodLine( int iHoodLine );									// pixel
M_EXTERN_C M_API int M_GetVehicle_HoodLine();
M_EXTERN_C M_API void M_SetVehicle_CenterLine( int iCenterLine );								// pixel
M_EXTERN_C M_API int M_GetVehicle_CenterLine();
M_EXTERN_C M_API void M_SetVehicle_CANData( unsigned int uiCANData );							// velocity | eVehicleCAN

M_EXTERN_C M_API void M_SetAlarm_DisableWarning( unsigned int uiDisableFlags );					// ALARM_LDW_DEPARTURE ~ ALARM_FCW_FORWARD_START
M_EXTERN_C M_API unsigned int M_GetAlarm_DisableWarning();

M_EXTERN_C M_API void M_SetLDW_ActiveVelocity( int iVelocity );									// km/h
M_EXTERN_C M_API int M_GetLDW_ActiveVelocity();
M_EXTERN_C M_API void M_SetLDW_SensitivityL( int iSensitivity );								// §¯
M_EXTERN_C M_API int M_GetLDW_SensitivityL();
M_EXTERN_C M_API void M_SetLDW_SensitivityR( int iSensitivity );								// §¯
M_EXTERN_C M_API int M_GetLDW_SensitivityR();
M_EXTERN_C M_API void M_SetLDW_AdjustResultLaneLength( int iRatio );							// 50~100%
M_EXTERN_C M_API void M_SetLDW_EnableCalibration( BOOL bEnable, BOOL bApplyInternally );

M_EXTERN_C M_API void M_SetFCW_ActiveVelocity( int iVelocity );									// km/h
M_EXTERN_C M_API int M_GetFCW_ActiveVelocity();
M_EXTERN_C M_API void M_SetFCW_TTC1( float fTTC1 );												// seconds
M_EXTERN_C M_API float M_GetFCW_TTC1();
M_EXTERN_C M_API void M_SetFCW_TTC2( float fTTC2 );												// seconds
M_EXTERN_C M_API float M_GetFCW_TTC2();
M_EXTERN_C M_API void M_SetFCW_CollisionAlarmType( unsigned int uiAlarmTypeFlags );				// FCW_ALERT_ALARM_ONCE ~ FCW_SERIOUS_ALARM_CONTINUE
M_EXTERN_C M_API unsigned int M_GetFCW_CollisionAlarmType();
M_EXTERN_C M_API void M_SetFCW_NearWarningDistance( int iDistance );							// §¯
M_EXTERN_C M_API int M_GetFCW_NearWarningDistance();
M_EXTERN_C M_API void M_SetFCW_FVSAlarmDelayTime( float fDelayTime );
M_EXTERN_C M_API float M_GetFCW_FVSAlarmDelayTime();

M_EXTERN_C M_API void M_SetMCL_InputImageDownscale( unsigned int uiDownscale );
M_EXTERN_C M_API void M_SetMCL_NearTargetDistance( double dDistance );							// §¯
M_EXTERN_C M_API void M_SetMCL_NearTargetHeight( double dHeight );								// §¯
M_EXTERN_C M_API void M_SetMCL_FarTargetDistance( double dDistance );							// §¯
M_EXTERN_C M_API void M_SetMCL_FarTargetHeight( double dHeight );								// §¯
M_EXTERN_C M_API void M_SetMCL_TiltAngleRange( double dMin, double dMax );						// degree
M_EXTERN_C M_API void M_SetMCL_YawAngleRange( double dMin, double dMax );						// degree
M_EXTERN_C M_API void M_SetMCL_CameraHeightRange( int iMin, int iMax );							// §¯

M_EXTERN_C M_API BOOL M_IsProcessing();
M_EXTERN_C M_API BOOL M_IsAsyncProcessing();
M_EXTERN_C M_API void M_SetCallback_NotifyComplete( pNotifyComplete pCallbackFunc );
M_EXTERN_C M_API void M_SetCallback_NotifyCompleteFCW( pNotifyComplete pCallbackFunc );
M_EXTERN_C M_API BOOL M_Create();
M_EXTERN_C M_API void M_Destroy();
M_EXTERN_C M_API BOOL M_SetInputImage( unsigned char* pInput );
M_EXTERN_C M_API void M_ProcessCommon();
M_EXTERN_C M_API void M_ProcessScene();
M_EXTERN_C M_API void M_ProcessLDW();
M_EXTERN_C M_API void M_ProcessFCW();
M_EXTERN_C M_API void M_ProcessACL();
M_EXTERN_C M_API void M_ProcessMCL();
M_EXTERN_C M_API sResultScene* M_GetSceneResult();
M_EXTERN_C M_API sResultLDW* M_GetLDWResult();
M_EXTERN_C M_API sResultFCW* M_GetFCWResult();
M_EXTERN_C M_API sResultACL* M_GetACLResult();
M_EXTERN_C M_API sResultMCL* M_GetMCLResult();

// Functions for DSP
M_EXTERN_C M_API void M_SetSharedAddressMainProc1( void* pAddress );		// For initialization
M_EXTERN_C M_API void M_SetSharedAddressMainProc2( void* pAddress );		// For real time (ARM->DSP)
M_EXTERN_C M_API void M_SetSharedAddressSubProc( void* pAddress );			// For real time (DSP->ARM)
M_EXTERN_C M_API void M_SetCallback_RequestSubProcRun( pRequestSubProcRun pCallbackFunc );
M_EXTERN_C M_API void M_NotifySubProcComplete();

#endif	// _MDASLIB_H_
