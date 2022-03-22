import styled from 'styled-components/native'

export const StyledContainer = styled.View`
    background-color: ${({color}) => color};
    flex: 1;
    align-items: center;
    justify-content: center;
`