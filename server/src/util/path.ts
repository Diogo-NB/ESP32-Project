import path from 'path';

const rootDir = require.main ? path.dirname(require.main.filename) : __dirname;

export default rootDir;
