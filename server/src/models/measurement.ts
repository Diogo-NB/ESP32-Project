import path from "path";
import rootDir from "../util/path";
import fs from "fs/promises";

const dataFilePath = path.join(path.dirname(rootDir), 'data', 'measurements.json');

export default class Measurement {

    public timeStamp: Date = new Date();

    constructor(public distance: number) { }

    toString() {
        return `Distance: ${this.distance}cm, TimeStamp: ${this.timeStamp}`;
    }

    async save() {
        try {
            const measurements = await Measurement.fetchAll();
            measurements.push(this);
            await fs.writeFile(dataFilePath, JSON.stringify(measurements));
            console.log('Saved : ', this.toString());
        } catch (error) {
            console.log('Error saving measurement ...');
            console.log(error);
        }
    }

    static async fetchAll(): Promise<Measurement[]> {
        try {
            const fileContent = await fs.readFile(dataFilePath, 'utf-8');
            return JSON.parse(fileContent) as Measurement[];
        } catch (error) {
            console.log('Error fetching measurements, returning an empty array and clearing cart ...');
            console.log(error);
            return [];
        }
    }
}