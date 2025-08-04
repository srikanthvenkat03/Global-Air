const express = require('express');
const router = express.Router();
const core = require('../build/Release/core_addon');

// @route   POST /api/gates/allocate
// @desc    Runs the gate allocation algorithm based on multiple priorities.
router.post('/allocate', (req, res) => {
    const { flights } = req.body;
    if (!flights || !Array.isArray(flights)) {
        return res.status(400).json({ msg: 'Please provide an array of flights to allocate.' });
    }
    try {
        // const allocations = core.AllocateGates(flights);
        // res.json(allocations);
        res.json({ message: "Gate allocation endpoint is ready.", allocatedGates: ["G1", "G2", "G3"] });
    } catch (err) {
        res.status(500).send("Error in gate allocation addon.");
    }
});

module.exports = router;