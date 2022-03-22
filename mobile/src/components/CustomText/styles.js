import styled from 'styled-components/native'

export const StyledText = styled.Text`
    font-size: ${({small}) => small ? 16 : 21};
    color: white;
    max-width: 240px;
    text-align: center;
`