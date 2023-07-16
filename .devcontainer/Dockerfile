# [Choice] jammy (22.04.2)
ARG VARIANT="jammy"
FROM ubuntu:${VARIANT}

# Restate the variant to use it later on in the llvm and cmake installations
ARG VARIANT

# Install necessary packages available from standard repos
RUN apt-get update -qq
RUN export DEBIAN_FRONTEND=noninteractive
RUN apt-get install --yes --quiet --no-install-recommends \
  software-properties-common=0.99.22.7 \
  wget=1.21.2-2ubuntu1 \
  apt-utils=2.4.9 \
  file=1:5.41-3 \
  zip=3.0-12build2 \
  openssh-client=1:8.9p1-3ubuntu0.1 \
  gpg-agent=2.2.27-3ubuntu2.1 \
  socat=1.7.4.1-3ubuntu4 \
  rsync=3.2.7-0ubuntu0.22.04.2 \
  make=4.3-4.1build1 \
  ninja-build=1.10.1-1 \
  git=1:2.34.1-1ubuntu1.9 \
  python3=3.10.6-1~22.04 \
  python3-pip=22.0.2+dfsg-1ubuntu0.3 \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# Install python dependencies
RUN python3 -m pip install --upgrade pip setuptools
RUN python3 -m pip install pathspec
RUN python3 -m pip install pyparsing

# Install conan
RUN python3 -m pip install --upgrade pip setuptools && \
  python3 -m pip install conan && \
  conan --version

# By default, anything you run in Docker is done as superuser.
# Conan runs some install commands as superuser, and will prepend `sudo` to
# these commands, unless `CONAN_SYSREQUIRES_SUDO=0` is in your env variables.
ENV CONAN_SYSREQUIRES_SUDO 0
# Some packages request that Conan use the system package manager to install
# a few dependencies. This flag allows Conan to proceed with these installations;
# leaving this flag undefined can cause some installation failures.
ENV CONAN_SYSREQUIRES_MODE enabled

# Install doxygen
RUN wget https://www.doxygen.nl/files/doxygen-1.9.7.linux.bin.tar.gz \
  mkdir -p "${HOME}/.local/bin" \
  tar -xC "${HOME}/.local/bin" -f doxygen-1.9.7.linux.bin.tar.gz \
  rm doxygen-1.9.7.linux.bin.tar.gz \
  echo "export PATH=\"${HOME}/.local/bin/doxygen-1.9.7/bin:${PATH}\"" >> "${HOME}/.bashrc" \
  export PATH="${HOME}/.local/bin/doxygen-1.9.7/bin:${PATH}" \
  doxygen -v

# User-settable versions:
# This Dockerfile should support gcc-[12] and clang-[15, 16, 17]
# Earlier versions of clang will require significant modifications to the IWYU section
ARG GCC_VER="12"
# Add gcc-${GCC_VER}
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
  apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
  apt-get install -y --no-install-recommends \
  gcc-${GCC_VER} g++-${GCC_VER} gdb \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# Set gcc-${GCC_VER} as default gcc
RUN update-alternatives --install /usr/bin/gcc gcc "$(which gcc-${GCC_VER})" 100
RUN update-alternatives --install /usr/bin/g++ g++ "$(which g++-${GCC_VER})" 100

ARG LLVM_VER="16"
# Add clang-${LLVM_VER}
ARG LLVM_URL="http://apt.llvm.org/${VARIANT}/"
ARG LLVM_PKG="llvm-toolchain-${VARIANT}-${LLVM_VER}"
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - 2>/dev/null && \
  add-apt-repository -y "deb ${LLVM_URL} ${LLVM_PKG} main" && \
  apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
  apt-get install -y --no-install-recommends \
  clang-${LLVM_VER} lldb-${LLVM_VER} lld-${LLVM_VER} clangd-${LLVM_VER} \
  llvm-${LLVM_VER}-dev libclang-${LLVM_VER}-dev clang-tidy-${LLVM_VER} \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# Set the default clang-tidy, so CMake can find it
RUN update-alternatives --install /usr/bin/clang-tidy clang-tidy "$(which clang-tidy-${LLVM_VER})" 1

# Set clang-${LLVM_VER} as default clang
RUN update-alternatives --install /usr/bin/clang clang "$(which clang-${LLVM_VER})" 100
RUN update-alternatives --install /usr/bin/clang++ clang++ "$(which clang++-${LLVM_VER})" 100

# Add current cmake/ccmake, from Kitware
ARG CMAKE_URL="https://apt.kitware.com/ubuntu/"
ARG CMAKE_PKG=${VARIANT}
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null \
  | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
  apt-add-repository -y "deb ${CMAKE_URL} ${CMAKE_PKG} main" && \
  apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
  apt-get install -y --no-install-recommends cmake cmake-curses-gui \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# Install editors
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
  apt-get install -y --no-install-recommends \
  neovim emacs nano \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# Install optional dependencies
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
  apt-get install -y --no-install-recommends \
  doxygen graphviz ccache cppcheck \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# Install include-what-you-use
ENV IWYU /home/iwyu
ENV IWYU_BUILD ${IWYU}/build
ENV IWYU_SRC ${IWYU}/include-what-you-use
RUN mkdir -p ${IWYU_BUILD} && \
  git clone --branch clang_${LLVM_VER} \
  https://github.com/include-what-you-use/include-what-you-use.git \
  ${IWYU_SRC}
RUN CC=clang-${LLVM_VER} CXX=clang++-${LLVM_VER} cmake -S ${IWYU_SRC} \
  -B ${IWYU_BUILD} \
  -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/usr/lib/llvm-${LLVM_VER} && \
  cmake --build ${IWYU_BUILD} -j && \
  cmake --install ${IWYU_BUILD}

# Per https://github.com/include-what-you-use/include-what-you-use#how-to-install:
# `You need to copy the Clang include directory to the expected location before
#  running (similarly, use include-what-you-use -print-resource-dir to learn
#  exactly where IWYU wants the headers).`
RUN mkdir -p "$(include-what-you-use -print-resource-dir 2>/dev/null)"
RUN ln -s "$(readlink -f /usr/lib/clang/${LLVM_VER}/include)" \
  "$(include-what-you-use -print-resource-dir 2>/dev/null)/include"

## Cleanup cached apt data we don't need anymore
RUN apt-get autoremove -y && apt-get clean && \
  rm -rf /var/lib/apt/lists/*

# Allow the user to set compiler defaults
ARG USE_CLANG
# if --build-arg USE_CLANG=1, set CC to 'clang' or set to null otherwise.
ENV CC=${USE_CLANG:+"clang"}
ENV CXX=${USE_CLANG:+"clang++"}
# if CC is null, set it to 'gcc' (or leave as is otherwise).
ENV CC=${CC:-"gcc"}
ENV CXX=${CXX:-"g++"}

# Include project
#ADD . /workspaces/modern_cpp_template
#WORKDIR /workspaces/modern_cpp_template

CMD ["/bin/bash"]
