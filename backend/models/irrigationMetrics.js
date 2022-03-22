const irrigationMetrics = (sequelize, DataTypes) => {
  const IrrigationMetrics = sequelize.define('IrrigationMetrics', {
    id: {
      type: DataTypes.INTEGER,
      autoIncrement: true,
      allowNull: false,
      primaryKey: true
    },
    duration: {
      type: DataTypes.INTEGER
    },
    initialMoisture: {
      type: DataTypes.INTEGER
    },
    finalMoisture: {
      type: DataTypes.INTEGER
    },
    status: {
      type: DataTypes.STRING
    }
  })
  return IrrigationMetrics
}

module.exports = irrigationMetrics
