<template>
<div>
    <div><h1>yo les bggggg ici c le classement</h1></div> 
    <v-table theme="light" density="default">
        <template v-slot:default>
        <thead>
            <tr>
            <th class="text-center">
                Classement   
            </th>
            <th class="text-center">
                Pseudo
            </th>
            <th class="text-center">
                Points
            </th>
            </tr>
        </thead>
        <tbody>
            <tr
            v-for="userData in usersData"
            :key="userData.classement"
            >
            <td>{{ userData.classement }}</td>
            <td>{{ userData.username }}</td>
            <td>{{ userData.points }}</td> 
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