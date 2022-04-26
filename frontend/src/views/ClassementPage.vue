<template>
<div>
    <v-table theme="light" density="default" style="margin-left:10%; margin-right:10%; margin-top:5% ; border-radius:4px ">
        <template v-slot:default>
        <thead style="background:rgb(50, 50, 50); color:white">
            <tr>
            <th class="text-center" style="padding-top:10px">
                <h3>#</h3>   
            </th>
            <th class="text-center" style="padding-top:10px">
                <h3>Pseudo</h3>
            </th>
            <th class="text-center" style="padding-top:10px">
                <h3>Parties gagnées</h3>
            </th>
            </tr>
        </thead>
        <tbody>
            <tr
            v-for="userData in usersData"
            :key="userData.classement"
            >
            <td v-if="userData.classement===1" style="font-weight: bolder; background:rgb(225, 209, 106)">{{ userData.classement }}</td>
            <td v-else-if="userData.classement===2" style="font-weight: bolder; background:rgb(195, 195, 195)">{{ userData.classement }}</td>
            <td v-else-if="userData.classement===3" style="font-weight: bolder; background:rgb(192, 137, 80)">{{ userData.classement }}</td>
            <td v-else>{{ userData.classement }}</td>
            <td v-if="userData.classement===1" style="font-weight: bolder; background:rgb(225, 209, 106)">{{ userData.username }}</td>
            <td v-else-if="userData.classement===2" style="font-weight: bolder; background:rgb(195, 195, 195)">{{ userData.username }}</td>
            <td v-else-if="userData.classement===3" style="font-weight: bolder; background:rgb(192, 137, 80)">{{ userData.username }}</td>
            <td v-else>{{ userData.username }}</td>
            <td v-if="userData.classement===1" style="font-weight: bolder; background:rgb(225, 209, 106)">{{ userData.points }}</td>
            <td v-else-if="userData.classement===2" style="font-weight: bolder; background:rgb(195, 195, 195)">{{ userData.points }}</td>
            <td v-else-if="userData.classement===3" style="font-weight: bolder; background:rgb(192, 137, 80)">{{ userData.points }}</td>
            <td v-else>{{ userData.points }}</td>
            </tr>
        </tbody>
        </template>
    </v-table>    
    <!-- <div v-for="userData in usersData" :key="userData.index">salut mec</div>  -->
</div>
</template>

<script>
// import SimpleTable from 
import axios from '@/api/axios-auth'

export default {
    classement: 'ClassementPage',
    // components: SimpleTable,
    data () {
        return {
            usersData: [],
            }
    },
    created() {
        axios.get(path).then((res)=> {
            res.data.users.forEach(element => {
                
                this.usersData.push(element);
            });
            })
    },
}
const path = `${process.env.VUE_APP_BACKEND_URL}/classement`;

</script>

<style scoped>
</style>