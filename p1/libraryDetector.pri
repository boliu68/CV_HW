# By Tian Fang tian.ft@gmail.com
# Feb. 4, 2013

# $$findIncludes(libraryName, libraryIncludePathVarName, libraryIncludePath, subDir, keyHeaders)
defineReplace(findIncludes){
    LIBNAME = $$1
    LIBINCLUDEPATHVARNAME = $$2
    LIBINCLUDEPATH = $$3
    ORIGINALLIBINCLUDEPATH = $${LIBINCLUDEPATH}
    SUBFOLDER = $$4
    KEYFILES = $$5

    isEmpty(LIBINCLUDEPATH) {
        for(tmp, INCLUDEPATH) {
            isEmpty(LIBINCLUDEPATH) {
                found = 1
                for(keyFile, KEYFILES) {
                    !exists($${tmp}/$${keyFile}) {
                        found = 0
                    }
                }

                contains(found, 1) {
                    message($${LIBNAME}: Header are found in $${tmp})
                    LIBINCLUDEPATH = $${tmp}
                }
            }
            isEmpty(LIBINCLUDEPATH) {
                found = 1
                for(keyFile, KEYFILES) {
                    !exists($${tmp}/$${SUBFOLDER}/$${keyFile}) {
                        found = 0
                    }
                }

                contains(found, 1) {
                    message($${LIBNAME}: Header are found in $${tmp}/$${SUBFOLDER})
                    LIBINCLUDEPATH = $${tmp}/$${SUBFOLDER}
                }
            }
        }
        isEmpty(LIBINCLUDEPATH) {
            message($${LIBNAME}: Header cannot be found automatically.)
            LIBINCLUDEPATH = /usr/include
            message($${LIBNAME}: Default include path $${LIBINCLUDEPATH} is set)
        }
    }

    # final test for whether the include path is found
    found = 1
    for(keyFile, KEYFILES) {
        !exists($${LIBINCLUDEPATH}/$${keyFile}) {
            message($${LIBNAME}: $${LIBINCLUDEPATH}/$${keyFile} cannot be found)
            found = 0
        }
    }
    contains(found, 1) {
        !contains(INCLUDEPATH, $${LIBINCLUDEPATH}) {
            !isEmpty(ORIGINALLIBINCLUDEPATH) {
                message($${LIBNAME}: include path are specified by $${LIBINCLUDEPATHVARNAME}.)
            }
            return($${LIBINCLUDEPATH})
        }
#        message($${LIBNAME}: $${LIBINCLUDEPATH} has already been added.)
        return ()
    }
    error($${LIBNAME}: Headers cannot be found in $${LIBINCLUDEPATH}. Please use INCLUDEPATH+=<PATH> or $${LIBINCLUDEPATHVARNAME}=<PATH> to specify the include path)
    return ()
}

# $$findLibraries(libraryName, libraryLIBLIBRARYPATHVarName, libraryPath, keyLibs)
# For the keyLibs, please use [DEBUGSUFFIX] to specify where the debug suffix should be added to test in debug configuration.
defineReplace(findLibraries){
    LIBNAME = $$1
    LIBLIBRARYPATHVARNAME = $$2
    LIBLIBRARYPATH = $$3
    ORIGINALLIBLIBRARYPATH = $${LIBLIBRARYPATH}
    KEYFILES = $$4

    LINKCOMMAND =

    DEBUGSUFFIX =
    CONFIG(debug, debug|release) {
        win32 {
            DEBUGSUFFIX = d
        }
        macx {
            DEBUGSUFFIX = _debug
        }
        linux-g++* {
            DEBUGSUFFIX = _debug
        }
    }

    isEmpty(LIBLIBRARYPATH) {
        for(tmp, LIBS) {
#            message($$find(tmp, -L))
            REALLIBPATH = $$find(tmp, -L)
            REALLIBPATH = $$unique(REALLIBPATH)
            !isEmpty(REALLIBPATH) {
                tmp = $$replace(tmp, -L, )
                isEmpty(LIBLIBRARYPATH) {
                    found = 1 
                    for(keyFile, KEYFILES) {
                        # Check debug version if in debug mode
                        CONFIG(debug, debug|release) {
                            DEBUGLIB = $${keyFile}#$$replace($${keyFile}, opencv, ddd)
                            DEBUGLIB ~= s/\\[DEBUGSUFFIX\\]/$${DEBUGSUFFIX}
                            message($${LIBNAME}: Checking debug lib: $${DEBUGLIB})
                            !exists($${tmp}/$${DEBUGLIB}) {
                                # message(cannot find $${tmp}/$${DEBUGLIB})
                                found = 0
                            }
                            contains(found, 1) {
                                LINKCOMMAND *= $${DEBUGLIB}
                            }
                            contains(found, 0) {
                                # if the debug file is not foumd, try to find the release lib instead.
                                keyFile ~= s/\\[DEBUGSUFFIX\\]/
                                message($${LIBNAME}: debug lib cannot found. testing $${tmp}/$${keyFile} instead)
                                exists($${tmp}/$${keyFile}) {
                                    message($${LIBNAME}: found $${tmp}/$${keyFile})
                                    found = 1
                                    LINKCOMMAND *= $${keyFile}
                                }
                            }
                            contains(found, 0) {
                                message($${LIBNAME}: neither $${keyFile} nor $${DEBUGLIB} is found.)
                            }
                        }
                        CONFIG(release, debug|release) {
                            keyFile ~= s/\\[DEBUGSUFFIX\\]/
                            message($${LIBNAME}: testing $${tmp}/$${keyFile})
                            !exists($${tmp}/$${keyFile}) {
                                message($${LIBNAME}: cannot find $${tmp}/$${keyFile})
                                found = 0
                            }
                            LINKCOMMAND *= $${keyFile}
                        }
                    }

                    contains(found, 1) {
                        message($${LIBNAME}: libraries are found in $${tmp})
                        LIBLIBRARYPATH = $${tmp}
                    }
                }
            }
        }
        isEmpty(LIBLIBRARYPATH) {
            message($${LIBNAME}: Libraries cannot be found automatically.)
            LIBLIBRARYPATH = /usr/lib
            message($${LIBNAME}: Default libraries path $${LIBLIBRARYPATH} is set)
        }
    }

    # final test for whether the library path is found
    found = 1
    LINKCOMMANDFINAL =

    for(keyFile, LINKCOMMAND) {
        !exists($${LIBLIBRARYPATH}/$${keyFile}) {
            message($${LIBNAME}: $${LIBLIBRARYPATH}/$${keyFile} cannot be found)
            found = 0
        }
        LINKFILE = $${keyFile}
        LINKFILE ~= s/\\*/
        LINKFILE ~= s/^lib/
        LINKCOMMANDFINAL += -l$${LINKFILE}
    }
    contains(found, 1) {

        !contains(LIBS, -L$${LIBLIBRARYPATH}) {
            !isEmpty(ORIGINALLIBLIBRARYPATH) {
                message($${LIBNAME}: libraries are specified by $${LIBLIBRARYPATHVARNAME}.)
            }
            message($${LIBNAME}: link command $${LINKCOMMANDFINAL})
            return(-L$${LIBLIBRARYPATH} $${LINKCOMMANDFINAL})
        }

        message($${LIBNAME}: link command $${LINKCOMMANDFINAL})
        return ($${LINKCOMMANDFINAL})
    }
    error($${LIBNAME}: Libraries cannot be found. Please use LIBS+=-L<PATH> or $${LIBLIBRARYPATHVARNAME}=<PATH> to specify the include path)
    return ()
}

#getLibraryPaths(KEYNAMES, TYPE) TYPE: any, static, dynamic
defineReplace(getLibraryPaths){
    KEYNAMES = $$1
    TYPESTR = $$2
    LIBPREFIX = lib
    STATIC_SUFFIX = .a
    DYNAMIC_SUFFIX =
    DEBUGSUFFIX =

    win32-msvc {
        LIBPREFIX =
    }
    win32-msvc {
        LIBPREFIX = .lib
    }
    win32-msvc {
        DYNAMIC_SUFFIX = .lib
    }
    win32-g++ {
        DYNAMIC_SUFFIX = .a
    }
    linux-g++* {
        DYNAMIC_SUFFIX = .so
    }
    macx {
        DYNAMIC_SUFFIX = .dylib
    }
    contains (config, debug)
    {
        win32 {
            DEBUGSUFFIX = d
        }
        macx {
            DEBUGSUFFIX = _debug
        }
    }

    KEYPATHS =
    for(tmp, KEYNAMES){
        isEmpty(TYPESTR) | contains(TYPESTR, any) {
            KEYPATHS += $${LIBPREFIX}$${tmp}*
        }

        contains(TYPESTR, static) {
            KEYPATHS += $${LIBPREFIX}$${tmp}$${STATIC_SUFFIX}
        }

        contains(TYPESTR, dynamic) {
            KEYPATHS += $${LIBPREFIX}$${tmp}$${DYNAMIC_SUFFIX}
        }
    }
    return($${KEYPATHS})
}

defineReplace(getLibraryLinkCommand){
    KEYNAMES = $$1

    LINKCOMMAND =
    for(tmp, KEYNAMES){
        LINKCOMMAND += -l$${tmp}
    }
    return($${LINKCOMMAND})
}

# dynamicLibFromSubdir(rootPath, projName, outputPrefix)
defineReplace(dynamicLibFromSubdir) {
    rootPath = $$1
    projName = $$2
    outputPrefix = $$3
    rootProjPath = $${rootPath}$$DIR_SEPARATOR$${projName}
    rootPro = $${rootProjPath}$$DIR_SEPARATOR$${projName}.pro
    subdirStr = $$fromfile($${rootPro}, SUBDIRS)

    DYNAMIC_SUFFIX =
    win32 {
        DYNAMIC_SUFFIX = .dll
    }
    linux-g++* {
        DYNAMIC_SUFFIX = .so
    }
    macx {
        DYNAMIC_SUFFIX = .dylib
    }

    extraBin =
    for(name,subdirStr){
        isEmpty(outputPrefix) {
            extraBin += $${rootProjPath}$$DIR_SEPARATOR$${name}$$DIR_SEPARATOR$${QMAKE_PREFIX_SHLIB}$${name}$${DYNAMIC_SUFFIX}
        }
        !isEmpty(outputPrefix) {
            extraBin += $${outputPrefix}$$DIR_SEPARATOR$${rootProjPath}$$DIR_SEPARATOR$${name}$$DIR_SEPARATOR$${QMAKE_PREFIX_SHLIB}$${name}$${DYNAMIC_SUFFIX}
        }
    }
    return($$extraBin)
}
