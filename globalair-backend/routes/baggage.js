const express = require('express');
const router = express.Router();
const core = require('../build/Release/core_addon');

router.post('/add', (req, res) => {
    const { id, type, passengerPriority, securityRisk } = req.body;
    if (!id || !type || passengerPriority === undefined || securityRisk === undefined) {
        return res.status(400).json({ msg: 'Missing baggage details.' });
    }
    try {
        res.json({ message: core.AddBaggage(id, type, passengerPriority, securityRisk) });
    } catch (err) {
        res.status(500).send("Error in baggage addon.");
    }
});

module.exports = router;