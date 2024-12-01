CREATE TABLE IF NOT EXISTS users
(
    id bigserial PRIMARY KEY
);

CREATE TABLE IF NOT EXISTS transactions
(
    id       bigserial PRIMARY KEY,
    user_id  bigint                   NOT NULL,
    category varchar                  NOT NULL,
    amount   double precision         NOT NULL,
    date     timestamp with time zone NOT NULL,
    CONSTRAINT fk_user FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
);