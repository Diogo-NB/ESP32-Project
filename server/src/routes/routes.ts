import express from "express";
import Measurement from "../models/measurement";
import path from "path";
import rootDir from "../util/path";

export const router = express.Router();

// Route to get a new distance measured to be saved
router.post("/add-measurement", (req, res, _next) => {
  const distance: number = req.body.distance;
  const measurement = new Measurement(+distance);
  measurement.save();
  res.send("Data received");
});

// Route to get a new distance measured to be saved
router.get("/add-measurement", (req, res, _next) => {
  res.sendFile(path.join(rootDir, "views", "index.html"));
});

// Route to get a new distance measured to be saved
router.get("/", (_req, res, _next) => {
  res.redirect("/add-measurement");
});

router.get("/remove-all", (_req, res, _next) => {
  Measurement.removeAll().then(() => {
    res.send("All data removed");
  });
});

router.get("/last-measurement", (_req, res, _next) => {
  Measurement.fetchLast().then((measurement) => {
    console.log(measurement[0]);
    res.send(measurement[0]);
  });
});
