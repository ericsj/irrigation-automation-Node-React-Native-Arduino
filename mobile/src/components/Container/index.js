import { StyledContainer } from "./styles";

const Container = (props) => {
    return <StyledContainer {...props}>{props.children}</StyledContainer>
}

export default Container