const express = require('express');
const router = express.Router();
const core = require('../build/Release/core_addon');

// @route   GET /api/dashboard/summary
// @desc    Gets live ranked data for the system monitoring dashboard.
router.get('/summary', (req, res) => {
    try {
        // const summary = core.GetDashboardSummary();
        // res.json(summary);
        res.json({
            message: "Monitoring dashboard endpoint is ready.",
            topDelays: ["Route A -> B", "Route C -> D"],
            baggageJams: ["Area 5"],
            riskyFlights: ["FL123"]
        });
    } catch (err) {
        res.status(500).send("Error getting dashboard summary.");
    }
});

module.exports = router;