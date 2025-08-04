const express = require('express');
const path = require('path');
const router = express.Router();
const core = require('../build/Release/core_addon');

router.post('/shortest-path', (req, res) => {
    const { start, end, weightType } = req.body;
    if (!start || !end || !weightType) return res.status(400).json({ msg: 'Missing inputs.' });
    const csvPath = path.join(__dirname, '..', '..', 'globalair-cpp-core', 'data', 'flights.csv');
    try {
        res.json(core.FindShortestPath(csvPath, start, end, weightType));
    } catch (err) {
        res.status(500).send("Error in pathfinding addon.");
    }
});

module.exports = router;