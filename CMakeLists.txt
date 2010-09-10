CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(KGF)

# ---------- Setup output Directories -------------------------
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/Bin )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/Bin )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/Bin )


ADD_SUBDIRECTORY(KGCommon)
ADD_SUBDIRECTORY(KGServer)
ADD_SUBDIRECTORY(KGClient)
