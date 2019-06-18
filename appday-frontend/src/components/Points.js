import React, {Component} from 'react';
import { Navbar } from './Navbar';

export default class Points extends Component {
    constructor(props) {
        super(props);

        this.state = {
            table: null,
            seasons: [],
            season: 2019,
            loaded: false,
            season_loaded: false,
            error: false
        }

        this.fetchPoints = this.fetchPoints.bind(this);
    }

    componentDidMount() {
        fetch('http://localhost:8000/api/v1/seasons')
            .then(raw_data => raw_data.json().then(data => {
                this.setState({seasons: data})
            })).catch(err => {
                this.setState({error: true})
            })
        
        fetch('http://localhost:8000/api/v1/pointstable/2019')
            .then(raw_data => raw_data.json().then(data => {
                this.setState({table: data, season: 2019, loaded: true})
            })).catch(err => {
                this.setState({error: true})
            })
    }

    fetchPoints(event) {
        var i = event.target.innerText
        this.setState({season_loaded: false});
        fetch('http://localhost:8000/api/v1/pointstable/' + i)
            .then(raw_data => raw_data.json().then(data => {
                this.setState({table: data, season: Number(i), season_loaded: true})
            })).catch(err => {
                this.setState({error: true})
            })
        debugger;
    }

    render() {
        if (this.state.loaded !== true) return <h1>Loading...</h1>
        return (
            <div>
            <Navbar/>
            <div className="jumbotron jumbotron-fluid">
                <div className="container">
                    <h1 className="display-5" style={{fontSize: '50px'}}>Points Table</h1>
                 </div>
            </div>
            <div className="col-sm-8" style={{margin: '0px auto', alignContent: 'center'}}>
                <DropDown curseason={this.state.season} seasons={this.state.seasons} onChange={this.fetchPoints}/>
                {
                    this.state.season_loaded === true  || this.state.loaded === true ?
                    <PointsTable points={this.state.table} season={this.state.season} gotoMatch={this.gotoMatch}/>:
                    <h1>Loading...</h1>
                }
            </div>
            </div>
        );
    }

}

const DropDown = props => {
    console.log(props, 'points')
    return (
        <div>
        <div className="btn-group">
        <button style={{
            textAlign: 'center',
            margin: '20px'
        
        }}       
        type="button" className="btn btn-info dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
           {props.curseason} 
        </button>
        <div className="dropdown-menu">
            {
                props.seasons.seasons.map((val, i) => {
                    return <a className="dropdown-item" onClick={props.onChange}>{val}</a>
                })
            }
        </div>
        </div>
        </div>
    )
}

const PointsTable = props => {
    console.log(props);
    return (
        
        <div>
            <table className="table table-hover table-striped table-dark">
                <thead>
                    <tr>
                    <th>
                        #
                    </th>
                    <th>
                        Team
                    </th>
                    <th>
                        Losses
                    </th>
                    <th>
                        Wins
                    </th>
                    <th>
                        Draws
                    </th>
                    <th>
                        Points
                    </th>
                    </tr>
                </thead>
            <tbody>
            {
                props.points.map((point, i) => {
                    return (
                        <tr>
                            <td>{i + 1}</td>
                            <td>{point[4]}</td>
                            <td>{point[0]}</td>
                            <td>{point[1]}</td>
                            <td>{point[2]}</td>
                            <td>{point[3]}</td>
                        </tr>
                    )
                })
            }
            </tbody>
            </table>
        </div>
    )
}