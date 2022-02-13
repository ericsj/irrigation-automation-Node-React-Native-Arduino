const irrigationMetricsDao = require('../dao/irrigationMetrics')
const systemStatusDao = require('../dao/systemStatus')

const initialIrrigationMetrics = {
  duration: 0,
  initialMoisture: 0,
  finalMoisture: 0
}
const initialSystemStatus = { status: '' }

const createInitialRecords = () => {
  irrigationMetricsDao.create(initialIrrigationMetrics)
    .then(result => console.log('initialIrrigationMetrics created'))
    .catch(err => console.log(err))
  systemStatusDao.create(initialSystemStatus)
    .then(result => console.log('initialSystemStatus created'))
    .catch(err => console.log(err))
}

module.exports = createInitialRecords
