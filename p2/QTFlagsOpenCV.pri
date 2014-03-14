# ----- setup  variables ------

OPENCVVER =
win32 {
    OPENCVVER = 242
}
macx {
    OPENCVVER =
}

# Check whether the libraries is enabled
!isEmpty(OPENCVENABLE) {
    message(OpenCV is enable)
    include(libraryDetector.pri)

    KEYHEADERS = opencv2/opencv.hpp
    KEYLIBNAME =
    win32 {
        KEYLIBNAME += opencv_core$$OPENCVVER[DEBUGSUFFIX] \
                    opencv_highgui$$OPENCVVER[DEBUGSUFFIX] \
                    opencv_imgproc$$OPENCVVER[DEBUGSUFFIX] \
                    opencv_flann$$OPENCVVER[DEBUGSUFFIX] \
                    opencv_calib3d$$OPENCVVER[DEBUGSUFFIX] \
                    opencv_video$$OPENCVVER[DEBUGSUFFIX] \
                    opencv_features2d$$OPENCVVER[DEBUGSUFFIX] \
                    opencv_legacy$$OPENCVVER[DEBUGSUFFIX] \
                    opencv_nonfree$$OPENCVVER[DEBUGSUFFIX]
    }
    !win32 {
        KEYLIBNAME += opencv_core[DEBUGSUFFIX] \
                    opencv_imgproc[DEBUGSUFFIX] \
                    opencv_highgui[DEBUGSUFFIX] \
                    opencv_features2d[DEBUGSUFFIX] \
                    opencv_calib3d[DEBUGSUFFIX] \
                    opencv_video[DEBUGSUFFIX] \
                    opencv_flann[DEBUGSUFFIX] \
                    opencv_legacy[DEBUGSUFFIX] \
                    opencv_ml[DEBUGSUFFIX] \
                    opencv_nonfree[DEBUGSUFFIX]
    }

    # ----- include header path ------
    INCLUDEPATH += $$findIncludes(OpenCV, OPENCVINCLUDEPATH, $${OPENCVINCLUDEPATH}, , $${KEYHEADERS})

    # ----- library path ------
    LIBS += $$findLibraries(OpenCV, OPENCVLIBPATH, $${OPENCVLIBPATH}, $$getLibraryPaths($${KEYLIBNAME}, any))

    # ----- post-build section -------
    !contains(DEFINES, ZETA_OPENCV_ENABLE) {
        DEFINES += ZETA_OPENCV_ENABLE
    }

    # ----- post-build section -------
}
