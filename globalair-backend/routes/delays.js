const express = require('express');
const router = express.Router();
const core = require('../build/Release/core_addon');

// @route   GET /api/delays/predict/:airport/:month
// @desc    Predicts delay for an airport and month using DP.
router.get('/predict/:airport/:month', (req, res) => {
    const { airport, month } = req.params;
    if (!airport || !month) {
        return res.status(400).json({ msg: 'Please provide airport and month.' });
    }
    try {
        // const prediction = core.PredictDelay(airport, parseInt(month));
        // res.json(prediction);
        res.json({ message: "Delay prediction endpoint is ready.", airport, month, mockDelay: 45 });
    } catch (err) {
        res.status(500).send("Error in delay prediction addon.");
    }
});

module.exports = router;    