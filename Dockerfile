FROM ubuntu:22.04 AS build

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libpq-dev \
    libssl-dev \
    wget \
    curl \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN git clone https://github.com/rbock/sqlpp11.git /opt/sqlpp11 && \
    cd /opt/sqlpp11 && \
    cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build build --target install

RUN git clone https://github.com/matthijs/sqlpp11-connector-postgresql.git /opt/sqlpp11-connector-postgresql && \
    cd /opt/sqlpp11-connector-postgresql && \
    cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build build --target install

RUN git clone https://github.com/HowardHinnant/date.git /opt/date && \
    cd /opt/date && \
    cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build build --target install

RUN cmake -S . -B build && \
    cmake --build build --target all

FROM ubuntu:22.04 AS runtime

RUN apt-get update && apt-get install -y \
    libpq-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

COPY --from=build /app/build/your_project_executable /usr/local/bin/your_project_executable

ENTRYPOINT ["start"]
