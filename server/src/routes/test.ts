import express from 'express';

export const router = express.Router();

router.get('/test', (_req: any, res: any, _next: any) => {
    console.log('OK');
    res.send('OK');
});

router.post('/test', (req: any, res: any, next: any) => {
    if ((req.body.distance as number) !== undefined) {
        const msg = `OK ... got ${req.body.distance}cm`;
        console.log(msg);
        res.send(msg);
    } else {
        res.status(400).send('Bad request');
    }
});

export default router;