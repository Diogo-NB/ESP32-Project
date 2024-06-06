import { Db, MongoClient, ServerApiVersion } from "mongodb";

const _mongodbUrl = "mongodb+srv://esp32-app:6X7OytyV3FRBqii0@dn-cluster.2wx04ik.mongodb.net/?retryWrites=true&w=majority&appName=DN-Cluster";

let _db: Db;

export async function connectMongoDB() {
  console.log(_mongodbUrl);
  // Connect the client to the server	(optional starting in v4.7)
  const client = await MongoClient.connect(_mongodbUrl, {
    serverApi: {
      version: ServerApiVersion.v1,
      strict: true,
      deprecationErrors: true,
    },
  });
  // Send a ping to confirm a successful connection
  _db = client.db("esp32");
}

export function getDb() {
  if (!_db) {
    throw new Error("Database not connected!");
  }
  return _db;
}
