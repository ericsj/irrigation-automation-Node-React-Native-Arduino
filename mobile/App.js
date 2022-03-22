import React, {useState, useEffect} from 'react'
import { Title, Container, IrrigationMetricsContainer,
  CustomText, TextContainer } from './src/components/'
import api from './src/services/api'

export default function App() {
  const [systemIsOk, setSystemIsOk] = useState()
  const [irrigationData, setIrrigationData] = useState()

  useEffect(() => {
    api
      .get(`/irrigation-metrics/`)
      .then(response => {
        console.log(response.data)
        if (response.data?.length) {
          setIrrigationData(response.data[0])
          setSystemIsOk(!Boolean(response.data[0].status))
        }
        else {
          setSystemIsOk(false)
        }
      })
      .catch(err => {
        console.log('Something went wrong\n', err)
      })
  },[])

  return (
    <Container color={systemIsOk ? '#0CFF87' : '#E3514B'}>
      <Title>Last irrigation data</Title>
      {irrigationData ? <IrrigationMetricsContainer>
        <CustomText>{`Initial moisture: ${irrigationData.initialMoisture}%`}</CustomText>
        <CustomText>{`Final moisture: ${irrigationData.finalMoisture}%`}</CustomText>
        <TextContainer>
          <CustomText>{`Irrigation duration:`}</CustomText>
          <CustomText>{`${irrigationData.duration}s`}</CustomText>
        </TextContainer>
        {systemIsOk
          ? <CustomText>{'Everything ok!'}</CustomText>
          : <TextContainer>
            <CustomText small>{'System problems:'}</CustomText>
            <CustomText>{irrigationData.status}</CustomText>
          </TextContainer>}
      </IrrigationMetricsContainer>
      : <CustomText>{'No data from server :(\nPlease start server and reopen the app'}</CustomText>}
    </Container>
  );
}

