import express from "express";
import bodyParser from "body-parser";

import { router as routes } from "./routes/routes";
import { router as testRoutes } from "./routes/test";

import dotenv from "dotenv";
dotenv.config();

import { connectMongoDB } from "./util/database";

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