import { Document, ObjectId, WithId } from "mongodb";
import { getDb } from "../util/database";

export default class Measurement {
  public _id?: ObjectId;

  constructor(
    public distance: number,
    public timeStamp: Date = new Date(),
    id?: ObjectId | string
  ) {}

  toString() {
    return `Distance: ${this.distance}cm, TimeStamp: ${this.timeStamp}`;
  }

  static fromJson(json: WithId<Document>): Measurement {
    const { _id, distance, timeStamp } = json;
    const measurement = new Measurement(distance, timeStamp, _id);
    measurement.timeStamp = timeStamp;
    return measurement;
  }

  async save() {
    try {
      getDb().collection("water-level").insertOne(this);
    } catch (error) {
      console.log("Error saving measurement ...");
      console.error(error);
    }
  }

  static async fetchLast() {
    return getDb()
      .collection("water-level")
      .find()
      .sort({ timeStamp: -1 })
      .map(Measurement.fromJson)
      .toArray();
  }

  static async removeAll() {
    return getDb().collection("water-level").deleteMany({});
  }

}
