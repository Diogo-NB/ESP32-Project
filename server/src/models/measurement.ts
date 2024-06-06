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
}
