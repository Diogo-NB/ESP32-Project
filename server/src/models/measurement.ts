import {getDb} from "../util/database";

export default class Measurement {
  public timeStamp: Date = new Date();

  constructor(public distance: number) {}

  toString() {
    return `Distance: ${this.distance}cm, TimeStamp: ${this.timeStamp}`;
  }

  async save() {
    try {
      getDb().collection("water-level").insertOne(this);
    } catch (error) {
      console.log("Error saving measurement ...");
      console.error(error);
    }
  }

  static async fetchAll() {
    try {
      return getDb().collection("water-level").findOne();
    } catch (error) {
      console.log("Error fetching measurements ...");
      console.error(error);
    }
  }
}
