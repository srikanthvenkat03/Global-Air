const express = require('express');
const router = express.Router();
const core = require('../build/Release/core_addon');

router.get('/trace/:id', (req, res) => {
    const baggageId = req.params.id;
    if (!baggageId) return res.status(400).json({ msg: 'Missing baggage ID.' });
    try {
        res.json(core.TraceBaggage(baggageId));
    } catch (err) {
        res.status(500).send("Error in lost baggage addon.");
    }
});

module.exports = router;