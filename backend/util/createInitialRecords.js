const irrigationMetricsDao = require('../dao/irrigationMetrics')

const initialIrrigationMetrics = {
  duration: 10,
  initialMoisture: 52,
  finalMoisture: 75,
  status: ''
}

const createInitialRecords = () => {
  irrigationMetricsDao.findAll()
    .then((result) => {
      if(!result.length) {
        irrigationMetricsDao.create(initialIrrigationMetrics)
          .then(() => console.log('initialIrrigationMetrics created'))
          .catch(err => console.log(err))
      }
    })
}

module.exports = createInitialRecords
