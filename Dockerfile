# syntax=docker/dockerfile:1

# Build image with:
# $ docker image build --rm --build-arg BUILD_DATE=$(date -u +'%FT%TZ') --tag jeffryklew/add-wrinkles-to-brain:1.0.1 --tag jeffryklew/add-wrinkles-to-brain:latest .
#
# Push image to dockerhub with:
# $ docker image push --all-tags jeffryklew/add-wrinkles-to-brain
#
# Run container with
# $ docker container run --rm jeffryklew/add-wrinkles-to-brain:latest

FROM ubuntu:22.10

# Install gcc, CMake, and Google Test
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    googletest \
    && rm -rf /var/lib/apt/lists/*

# Create/change to non-root USER
# Also change ownerhip of ddd-wrinkles-to-brain folder to non-root
RUN groupadd -r jklewgroup \
    && useradd --no-log-init -r -g jklewgroup jklewuser \
    && mkdir -p /home/add-wrinkles-to-brain \
    && chown -R jklewuser:jklewgroup /home/add-wrinkles-to-brain
USER jklewuser

# Metadata from https://github.com/opencontainers/image-spec/blob/main/annotations.md
ARG BUILD_DATE
LABEL org.opencontainers.image.created=${BUILD_DATE}
LABEL org.opencontainers.image.authors="Jeffry Lew"
LABEL org.opencontainers.image.url="https://hub.docker.com/repository/docker/jeffryklew/add-wrinkles-to-brain"
LABEL org.opencontainers.image.source="https://github.com/jeffrylew/add-wrinkles-to-brain/Dockerfile"
LABEL org.opencontainers.image.title="Add Wrinkles to Brain"
LABEL org.opencontainers.image.base.name="docker.io/library/ubuntu:22.10"
LABEL org.opencontainers.image.version="1.0.1"

# Copy source code from repo
COPY . /home/add-wrinkles-to-brain

# Build source code
WORKDIR /home/add-wrinkles-to-brain
RUN cmake -S . -B build \
    && cmake --build build -j 2

# Run tests upon container start
CMD [ "ctest", "--output-on-failure", "--test-dir", "build" ]