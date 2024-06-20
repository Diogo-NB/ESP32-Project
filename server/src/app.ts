import express from "express";
import bodyParser from "body-parser";

import { router as routes } from "./routes/routes";
import { router as testRoutes } from "./routes/test";

import path from "path";

import dotenv from "dotenv";

import { connectMongoDB } from "./util/database";
import rootDir from "./util/path";

dotenv.config({ path: path.resolve(rootDir, "../.env") });

const app = express();

app.use(bodyParser.urlencoded({ extended: true }));

app.use(bodyParser.json());

app.use(routes);

app.use(testRoutes);

app.use((_req, res, _next) => {
  res.status(404).send("404 - Page not found");
});

// Create a local server to receive data from
app.listen(3000);

connectMongoDB().catch(console.error);
