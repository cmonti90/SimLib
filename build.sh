#!/bin/sh

buildToDir="build"

curDir=${PWD}
oldDir=${OLDPWD}

export HDF5LIB_DIR="/home/cmonti/Documents/Coding/Libraries/SimLib/HDF5/1.12.0/share/cmake/hdf5"
export MATHLIB_DIR="/home/cmonti/Documents/Coding/Libraries/myMathLib/install/lib64/cmake/mathlib"
export PUBSUBLIB_DIR="/home/cmonti/Documents/Coding/Libraries/PubSub/install/lib64/cmake/PubSub"

SCRIPT_DIR="$( dirname -- "${BASH_SOURCE[0]}" )"

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
SCRIPT_DIR="$( dirname "$SOURCE" )"

if [ -d "${SCRIPT_DIR}/${buildToDir}" ]
then
    echo "Removing current build..."
    rm -rf "${SCRIPT_DIR}/${buildToDir}"
    echo "Done!"
fi

if [ -d "${SCRIPT_DIR}/install" ]
then
    echo "Removing current install..."
    rm -rf "${SCRIPT_DIR}/install"
    echo "Done!"
fi

mkdir -p "${SCRIPT_DIR}/${buildToDir}"
mkdir -p "${SCRIPT_DIR}/install"

echo "Configuring build..."
cmake -S "${SCRIPT_DIR}" -B "${SCRIPT_DIR}/${buildToDir}"

if [ ${?} -ne 0 ]
then
  echo "Configuration failed"
  echo "Exiting"
  
  cd ${curDir}
  export OLDPWD=${oldDir}

  exit 1
fi

echo "Building library..."
cmake --build "${SCRIPT_DIR}/${buildToDir}"
if [ ${?} -ne 0 ]
then
  echo "Build failed"
  echo "Exiting"

  cd ${curDir}
  export OLDPWD=${oldDir}

  exit 1
fi

echo "Build complete!"

echo "Installing library..."
cmake --install "${SCRIPT_DIR}/${buildToDir}" --prefix "${SCRIPT_DIR}/install"

cd ${curDir}
export OLDPWD=${oldDir}

exit 0