#!/bin/bash

checkabortfailed()
{
    if [ $1 -eq 0 ]
    then
      echo "INFO: Step finished successfully"
    else
      echo "ERROR: An error occurred. aborting..."
      exit 1
    fi
}

get_cur_dir() {
    SOURCE="${BASH_SOURCE[0]}"

    # resolve $SOURCE until the file is no longer a symlink
    while [ -h "$SOURCE" ]; do
      DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
      SOURCE="$(readlink "$SOURCE")"
      # if $SOURCE was a relative symlink, we need to resolve it relative to
      # the path where the symlink file was located
      [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
    done
    DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
}

get_cur_dir


export TARGET_OS=`uname -s`

echo "Remove old builds"
rm -rf $DIR/build

mkdir $DIR/build
#######################################################################
if [ "${TARGET_OS}" == "Linux" ] || [ "${TARGET_OS}" == "Darwin" ]
then
  #TODO: install the following needed tools
  # xsltproc, lcov, doxygen
  pushd $DIR/build
  echo "INFO: Build for [${TARGET_OS}]"
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  checkabortfailed $?

  echo "INFO: Count number of CPU cores on this machine"
  CPU_CORES_COUNT=`grep -c ^processor /proc/cpuinfo`
  #CPU_CORES_COUNT=1
  echo "INFO: There are [${CPU_CORES_COUNT}] processor cores in this machine"

  echo "INFO: Build project"
  make -j${CPU_CORES_COUNT}
  checkabortfailed $?

  
  popd
else
  pushd $DIR/build
  CPU_CORES_COUNT=${NUMBER_OF_PROCESSORS}

  echo "Build for ${TARGET_OS}"
  cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 14 2015 Win64" ..
  checkabortfailed $?

  echo "Add MSBuild to path"
  export PATH="C:\Program Files (x86)\MSBuild\14.0\Bin":$PATH
  MSBuild.exe *.sln /maxcpucount:${CPU_CORES_COUNT}
  checkabortfailed $?

  popd
fi
