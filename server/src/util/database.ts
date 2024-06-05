import { MongoClient, ServerApiVersion } from "mongodb";

const _mongodbUrl = process.env.MONGODB_URL ?? "";

export async function connectMongoDB() {
  // Connect the client to the server	(optional starting in v4.7)
  const client = await MongoClient.connect(_mongodbUrl, {
    serverApi: {
      version: ServerApiVersion.v1,
      strict: true,
      deprecationErrors: true,
    },
  });
  // Send a ping to confirm a successful connection
  await client.db("esp32").command({ ping: 1 });
  console.log("Pinged your deployment. You successfully connected to MongoDB!");
}
